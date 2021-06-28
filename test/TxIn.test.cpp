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
        
    }
}