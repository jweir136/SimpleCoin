#include <include/catch2/catch.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>
#include <iostream>
#include <ctime>
#include <string>

TEST_CASE("TxIn", "[txin constructor]") {
    srand(time(NULL));

    int block;
    int tx;
    int amount;
    

    for (int i = 0; i < 10; i++) {
        block = rand() % 100000000;
        tx = rand() % 100000000;
        amount = rand() % 1000;

        Tx::TxIn* txin = new Tx::TxIn(block, tx, amount);

        REQUIRE(txin->block == block);
        REQUIRE(txin->tx == tx);
        REQUIRE(txin->amount == amount);

        delete txin;
        
    }
}

TEST_CASE("TxIn Serialize", "[txin serialize]") {
    srand(time(NULL));

    int block;
    int tx;
    int amount;
    std::size_t hash;
    Tx::TxIn* txin;
    Tx::TxIn* newtxin;

    for (int i = 0; i < 100; i++) {
        block = rand() % 100000000;
        tx = rand() % 100000000;
        amount = rand() % 1000;

        txin = new Tx::TxIn(block, tx, amount);
        newtxin = new Tx::TxIn(txin->serialize());

        REQUIRE(newtxin->amount == amount);
        REQUIRE(newtxin->block == block);
        REQUIRE(newtxin->tx == tx);
        //REQUIRE(newtxin->hash == hash);


        delete txin;
        delete newtxin;
        
    }
}

TEST_CASE("TxIns", "[txins]") {
    Tx::TxIns* txins = new Tx::TxIns();

    srand(time(NULL));

    int block;
    int tx;
    int amount;
    

    for (int i = 0; i < 5; i++) {
        block = rand() % 100000000;
        tx = rand() % 100000000;
        amount = rand() % 1000;

        txins->add_txin(block, tx, amount);
        
        REQUIRE(txins->txins[i].amount == amount);
        REQUIRE(txins->txins[i].block == block);
        REQUIRE(txins->txins[i].tx == tx);
    }

    delete txins;
}

TEST_CASE("TxOut", "[txout]") {
    Tx::TxOut* txout;
    Tx::TxOut* newtxout;
    unsigned int id;
    unsigned int amount;

    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        amount = rand() % 1000;
        id = rand() % 100000000;

        txout = new Tx::TxOut(amount, id);

        REQUIRE(txout->amount == amount);
        REQUIRE(txout->reciever == id);

        delete txout;
    }

    for (int i = 0; i < 100; i++) {
        amount = rand() % 1000;
        id = rand() % 1000;

        txout = new Tx::TxOut(amount, id);

        newtxout = new Tx::TxOut(txout->serialize());

        REQUIRE(newtxout->amount == amount);
        REQUIRE(newtxout->reciever == id);

        delete txout;
        delete newtxout;
    }
}

TEST_CASE("TxOuts", "[txouts]") {
    Tx::TxOuts* txouts = new Tx::TxOuts();

    srand(time(NULL));

    unsigned int id;
    unsigned int amount;
    

    for (int i = 0; i < 5; i++) {
        amount = rand() % 1000;
        id = rand() % 1000;

        txouts->add_txout(amount, id);
        
        REQUIRE(txouts->txouts[i].amount == amount);
        REQUIRE(txouts->txouts[i].reciever == id);
    }

    delete txouts;
}