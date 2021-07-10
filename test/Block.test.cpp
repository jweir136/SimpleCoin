#include <include/catch2/catch.hpp>
#include <SimpleCoin/Block/Block.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>
#include <iostream>
#include <ctime>
#include <string>

TEST_CASE("block", "[]") {
    srand(time(NULL));
    unsigned int amount;
    unsigned long reciever;

    Tx::TxOuts* txouts = new Tx::TxOuts();

    unsigned long block;
    unsigned long tx;

    Tx::TxIns* txins = new Tx::TxIns();

    Tx::Transaction* trans;
    Block* blockobj = new Block();
    Block* blockobj2;

    for (int i = 0; i < 100; i++) {
        amount = rand() % 1000;
        reciever = rand() % 1000;

        txouts->add_txout(amount, reciever);

        block = rand() % 1000;
        tx = rand() % 1000;

        txins->add_txin(amount, block, tx);

        trans = new Tx::Transaction(txins->to_json(), txouts->to_json());
        blockobj->add_transaction(trans->to_json());

        blockobj2 = new Block(blockobj->to_json());

        REQUIRE(blockobj->epoch == blockobj2->epoch);
        REQUIRE(blockobj->hash == blockobj2->hash);
        REQUIRE(blockobj->nonce == blockobj2->nonce);
    }

    delete txins;
    delete txouts;
    delete trans;
    delete blockobj;
    delete blockobj2;
};

/*
TEST_CASE("nonce", "[]") {
    std::cout << "Computing Nonce..." << std::endl;

    srand(time(NULL));
    unsigned int amount;
    unsigned long reciever;

    Tx::TxOuts* txouts = new Tx::TxOuts();

    unsigned long block;
    unsigned long tx;

    Tx::TxIns* txins = new Tx::TxIns();

    Tx::Transaction* trans;
    Block* blockobj = new Block();

    for (int i = 0; i < 1; i++) {
        amount = rand() % 1000;
        reciever = rand() % 1000;

        txouts->add_txout(amount, reciever);

        block = rand() % 1000;
        tx = rand() % 1000;

        txins->add_txin(amount, block, tx);

        trans = new Tx::Transaction(txins->to_json(), txouts->to_json());
        blockobj->add_transaction(trans->to_json());
        blockobj->compute_nonce();

        REQUIRE((blockobj->hash + blockobj->nonce) % 1000 == 0);
    }

    delete txins;
    delete txouts;
    delete trans;
    delete blockobj;
}
*/