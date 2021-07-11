#ifndef CRYPTO_H
#define CRYPTO_H

#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/ec.h>
#include <openssl/pem.h>

namespace ECDSA {

    inline void generate_keys(std::string pub_key_filepath, std::string priv_key_filepath) {
        EC_KEY* ec_key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);

        if (!EC_KEY_generate_key(ec_key))
            throw std::runtime_error("Error: Can't generate keys");
        if (!EC_KEY_check_key(ec_key))
            throw std::runtime_error("Error: Generated keys failed check");

        BIO* bio = BIO_new_fp(stdout, 0);
        BIO_free(bio);

        {
            FILE* f = fopen(pub_key_filepath.c_str(), "w");
            PEM_write_EC_PUBKEY(f, ec_key);
            fclose(f);
        }
        {
            FILE* f = fopen(priv_key_filepath.c_str(), "w");
            PEM_write_ECPrivateKey(f, ec_key, NULL, NULL, 0, NULL, NULL);
            fclose(f);
        }

        EC_KEY_free(ec_key);
    }

    inline std::string sign(const std::string priv_key_filepath, const std::string input) {
        std::string signature;

        FILE* f = fopen(priv_key_filepath.c_str(), "r");
        EC_KEY* ec_key = PEM_read_ECPrivateKey(f, NULL, NULL, NULL);
        fclose(f);

        if (!EC_KEY_check_key(ec_key))
            throw std::runtime_error("Error: Private key failed check");

        EVP_PKEY* key = EVP_PKEY_new();

        if (!EVP_PKEY_assign_EC_KEY(key, ec_key))
            throw std::runtime_error("Error: Key could not be assigned");

        EVP_PKEY_CTX* key_ctx = EVP_PKEY_CTX_new(key, NULL);

        EVP_PKEY_sign_init(key_ctx);
        EVP_PKEY_CTX_set_signature_md(key_ctx, EVP_sha256());

        std::size_t sig_len = 0;
        EVP_PKEY_sign(key_ctx, NULL, &sig_len, (unsigned char *)&input, input.length());
        signature.assign(sig_len, 0);
        EVP_PKEY_sign(key_ctx, (unsigned char *)&signature[0], &sig_len, (unsigned char *)&input, input.length());

        EVP_PKEY_CTX_free(key_ctx);
        EVP_PKEY_free(key);

        return signature;
    }

    inline bool verify(std::string pub_key_filepath, std::string expected, std::string signature, bool use_file = true) {
        FILE* f = fopen(pub_key_filepath.c_str(), "r");
        EC_KEY* ec_key = PEM_read_EC_PUBKEY(f, NULL, NULL, NULL);
        fclose(f);

        EVP_PKEY* key = EVP_PKEY_new();

        EVP_PKEY_assign_EC_KEY(key, ec_key);

        EVP_PKEY_CTX* key_ctx = EVP_PKEY_CTX_new(key, NULL);
        EVP_PKEY_verify_init(key_ctx);
        
        EVP_PKEY_CTX_set_signature_md(key_ctx, EVP_sha256());
        std::size_t sig_len = 0;

        bool ret = EVP_PKEY_verify(key_ctx, (unsigned char *)&signature[0], signature.length(), (unsigned char *)&expected, expected.length());

        EVP_PKEY_CTX_free(key_ctx);
        EVP_PKEY_free(key);

        return ret;
    }

}

#endif
