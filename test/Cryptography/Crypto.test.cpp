#define CATCH_CONFIG_MAIN
#include <include/catch2/catch.hpp>
#include <SimpleCoin/Cryptography/crypto.hpp>
#include <iostream>
#include <string>

TEST_CASE("signing", "[]") {
    std::string test = std::to_string(123);

    ECDSA::generate_keys("test/Cryptography/ryan_pub.pem", "test/Cryptography/ryan_priv.pem");
    std::string sig = ECDSA::sign("test/Cryptography/ryan_priv.pem", test);

    REQUIRE(ECDSA::verify("test/Cryptography/ryan_pub.pem", test, sig));
};

TEST_CASE("signing-with-string", "[]") {
    std::string test = "abc";
    std::string reciever = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEc6ukAACrN/vwpK9Ym8Cl4jd3PO0t\nlUuLPtX3Eq3bDvQ5rFAMeZbm4oE4bNM9sIieBescJL3n6yxJ6Z6EtXvMFQ==\n-----END PUBLIC KEY-----";
    std::string r = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEOr1LMSGxb7P3JoCoj/Z4J93C09Mi\nUT5PtVSGWRJRUisRdxJFmVBEB+52T6nY1snpWW9kgQizJcebwaTJtO4yXw==\n-----END PUBLIC KEY-----";

    std::string sig = ECDSA::sign("test/Cryptography/ryan_priv.pem", test);

    bool passed = ECDSA::verify_from_string(reciever, test, sig);
    REQUIRE(passed);

    sig = ECDSA::sign("test/Cryptography/ryan_priv.pem", test);
    std::cout << ECDSA::verify_from_string(r, test, sig);
};
