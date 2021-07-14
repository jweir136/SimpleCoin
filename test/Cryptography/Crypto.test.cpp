#define CATCH_CONFIG_MAIN
#include <include/catch2/catch.hpp>
#include <SimpleCoin/Cryptography/crypto.hpp>
#include <iostream>
#include <string>

TEST_CASE("signing", "[]") {
    std::string test = std::to_string(123);

    ECDSA::generate_keys("test/Cryptography/pub2.pem", "test/Cryptography/priv2.pem");
    std::string sig = ECDSA::sign("test/Cryptography/priv.pem", test);

    REQUIRE(ECDSA::verify("test/Cryptography/pub.pem", test, sig));
};

TEST_CASE("signing-with-string", "[]") {
    std::string test = "abc";
    std::string reciever = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEkculYE8/uBwUC8tST0DTZ0bWQ+gi\nOdsPVDp0t4657MyHvwZIIh9giKvNYcF0uuw3hrMBpX2nESD8ypdiUNlgDg==\n-----END PUBLIC KEY-----";

    std::string sig = ECDSA::sign("test/Cryptography/priv.pem", test);

    bool passed = ECDSA::verify_from_string(reciever, test, sig);
    REQUIRE(passed);
};
