#define CATCH_CONFIG_MAIN
#include <include/catch2/catch.hpp>
#include <SimpleCoin/Cryptography/crypto.hpp>
#include <iostream>
#include <string>

TEST_CASE("signing", "[]") {
    std::string test = "abc";

    ECDSA::generate_keys("test/Cryptography/pub.pem", "test/Cryptography/priv.pem");
    std::string sig = ECDSA::sign("test/Cryptography/priv.pem", test);

    REQUIRE(ECDSA::verify("test/Cryptography/pub.pem", test, sig));
};
