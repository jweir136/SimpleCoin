#include <include/catch2/catch.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>
#include <iostream>
#include <ctime>
#include <string>

TEST_CASE("txin", "[]") {
    srand(time(NULL));
    unsigned int amount;
    unsigned long block;
    unsigned long tx;
    Tx::TxIn* txin;

    for (int i = 0; i < 10; i++) {
        amount = rand() % 10000;
        block = rand() % 100000;
        tx = rand() % 10000;

        Tx::TxIn* txin;
        txin = new Tx::TxIn(amount, block, tx);
        Tx::TxIn* newtxin;
        newtxin = new Tx::TxIn(txin->to_json());

        REQUIRE(txin->amount == newtxin->amount);
        REQUIRE(txin->block == newtxin->block);
        REQUIRE(txin->tx == newtxin->tx);

        delete newtxin;
        delete txin;
    }
}

TEST_CASE("txins","[]") {
    srand(time(NULL));
    unsigned int amount;
    unsigned long block;
    unsigned long tx;

    Tx::TxIns* txins = new Tx::TxIns();
    Tx::TxIns* newtxins;

    for (int i = 0; i < 10; i++) {
        amount = rand() % 10000;
        block = rand() % 100000;
        tx = rand() % 10000;

        txins->add_txin(amount, block, tx);
        newtxins = new Tx::TxIns(txins->to_json());

        REQUIRE(txins->json_string == newtxins->json_string);

        delete newtxins;
    }

    delete txins;
}

TEST_CASE("txout", "[]") {
    srand(time(NULL));
    unsigned int amount;
    std::string key = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEvo2EhDT60gPW+8BRq7iB0SkBn+UE\nSOcts5pJSiPb+7uL6jrVQYyyyyVvePXwbMvQBAkl7MuycLry0w9UTEwNDg==\n-----END PUBLIC KEY-----";
    Tx::TxOut* txout;

    for (int i = 0; i < 10; i++) {
        amount = rand() % 10000;

        Tx::TxOut* txout;
        txout = new Tx::TxOut(amount, key);
        Tx::TxOut* newtxout;
        newtxout = new Tx::TxOut(txout->to_json());

        REQUIRE(txout->amount == newtxout->amount);
        REQUIRE(txout->reciever == newtxout->reciever);

        delete newtxout;
        delete txout;
    }
}

TEST_CASE("txouts","[]") {
    srand(time(NULL));
    unsigned int amount;
    std::string key = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEvo2EhDT60gPW+8BRq7iB0SkBn+UE\nSOcts5pJSiPb+7uL6jrVQYyyyyVvePXwbMvQBAkl7MuycLry0w9UTEwNDg==\n-----END PUBLIC KEY-----";

    Tx::TxOuts* txins = new Tx::TxOuts();
    Tx::TxOuts* newtxins;

    for (int i = 0; i < 10; i++) {
        amount = rand() % 10000;

        txins->add_txout(amount, key);
        newtxins = new Tx::TxOuts(txins->to_json());

        REQUIRE(txins->json_string == newtxins->json_string);

        delete newtxins;
    }

    delete txins;
}

TEST_CASE("trans", "[]") {
    srand(time(NULL));
    unsigned int amount;
    std::string key = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEvo2EhDT60gPW+8BRq7iB0SkBn+UE\nSOcts5pJSiPb+7uL6jrVQYyyyyVvePXwbMvQBAkl7MuycLry0w9UTEwNDg==\n-----END PUBLIC KEY-----";

    Tx::TxOuts* txouts = new Tx::TxOuts();

    unsigned long block;
    unsigned long tx;

    Tx::TxIns* txins = new Tx::TxIns();

    Tx::Transaction* trans;
    Tx::Transaction* trans2;

    for (int i = 0; i < 10; i++) {
        amount = rand() % 1000;

        txouts->add_txout(amount, key);

        block = rand() % 1000;
        tx = rand() % 1000;

        txins->add_txin(amount, block, tx);

        trans = new Tx::Transaction(txins->to_json(), txouts->to_json(), key);
        trans2 = new Tx::Transaction(trans->to_json());

        trans->sign_transaction("test/Cryptography/jake_priv.pem");

        REQUIRE(trans->epoch == trans2->epoch);
        REQUIRE(trans->hash == trans2->hash);
        REQUIRE(trans->txins == trans2->txins);
        REQUIRE(trans->txouts == trans2->txouts);
        REQUIRE(trans->author_key == trans2->author_key);

        REQUIRE(trans->verify_transaction());
        REQUIRE(trans->is_balanced());
    }

    delete txins;
    delete txouts;
    delete trans;
    delete trans2;
}