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