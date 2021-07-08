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

    for (int i = 0; i < 100; i++) {
        amount = rand() % 10000;
        block = rand() % 100000;
        tx = rand() % 10000;

        Tx::TxIn* txin;
        txin = new Tx::TxIn(amount, block, tx);
        Tx::TxIn* newtxin;
        newtxin = new Tx::TxIn(txin->json());

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

    for (int i = 0; i < 100; i++) {
        amount = rand() % 10000;
        block = rand() % 100000;
        tx = rand() % 10000;

        txins->add_txin(amount, block, tx);
        newtxins = new Tx::TxIns(txins->json());

        REQUIRE(txins->txins == newtxins->txins);

        delete newtxins;
    }

    delete txins;
}

TEST_CASE("txout", "[]") {
    srand(time(NULL));
    unsigned int amount;
    unsigned long reciever;
    Tx::TxOut* txout;

    for (int i = 0; i < 100; i++) {
        amount = rand() % 10000;
        reciever = rand() % 100000;

        Tx::TxOut* txout;
        txout = new Tx::TxOut(amount, reciever);
        Tx::TxOut* newtxout;
        newtxout = new Tx::TxOut(txout->json());

        REQUIRE(txout->amount == newtxout->amount);
        REQUIRE(txout->reciever == newtxout->reciever);

        delete newtxout;
        delete txout;
    }
}

TEST_CASE("txouts","[]") {
    srand(time(NULL));
    unsigned int amount;
    unsigned long reciever;

    Tx::TxOuts* txins = new Tx::TxOuts();
    Tx::TxOuts* newtxins;

    for (int i = 0; i < 100; i++) {
        amount = rand() % 10000;
        reciever = rand() % 100000;

        txins->add_txout(amount, reciever);
        newtxins = new Tx::TxOuts(txins->json());

        REQUIRE(txins->txouts == newtxins->txouts);

        delete newtxins;
    }

    delete txins;
}

TEST_CASE("trans", "[]") {
    srand(time(NULL));
    unsigned int amount;
    unsigned long reciever;

    Tx::TxOuts* txouts = new Tx::TxOuts();

    unsigned long block;
    unsigned long tx;

    Tx::TxIns* txins = new Tx::TxIns();

    Tx::Transaction* trans;
    Tx::Transaction* trans2;

    for (int i = 0; i < 100; i++) {
        amount = rand() % 1000;
        reciever = rand() % 1000;

        txouts->add_txout(amount, reciever);

        block = rand() % 1000;
        tx = rand() % 1000;

        txins->add_txin(amount, block, tx);

        trans = new Tx::Transaction(txins->json(), txouts->json());
        trans2 = new Tx::Transaction(trans->json());

        REQUIRE(trans->epoch == trans2->epoch);
        REQUIRE(trans->hash == trans2->hash);
        REQUIRE(trans->txins == trans2->txins);
        REQUIRE(trans->txouts == trans2->txouts);
    }

    delete txins;
    delete txouts;
    delete trans;
    delete trans2;
}