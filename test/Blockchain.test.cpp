#include <include/catch2/catch.hpp>
#include <SimpleCoin/Block/Block.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>
#include <SimpleCoin/Blockchain/Blockchain.hpp>
#include <iostream>
#include <ctime>
#include <string>

TEST_CASE("blockchain", "[]") {
    srand(time(NULL));
    unsigned int amount;
    unsigned long reciever;

    Tx::TxOuts* txouts = new Tx::TxOuts();

    unsigned long block;
    unsigned long tx;

    Tx::TxIns* txins = new Tx::TxIns();

    Tx::Transaction* trans;
    Block* blockobj = new Block();
    Blockchain* chain = new Blockchain();
    Blockchain* chain2;

    for (int i = 0; i < 100; i++) {
        amount = rand() % 1000;
        reciever = rand() % 1000;

        txouts->add_txout(amount, reciever);

        block = rand() % 1000;
        tx = rand() % 1000;

        txins->add_txin(amount, block, tx);

        trans = new Tx::Transaction(txins->json(), txouts->json());
        blockobj->add_transaction(trans->json());

        chain->add_block(blockobj->json());

        chain2 = new Blockchain(chain->json());

        REQUIRE(chain->blocks == chain2->blocks);
        REQUIRE(chain->hash == chain2->hash);
    }

    chain->verify();

    delete txins;
    delete txouts;
    delete trans;
    delete blockobj;
    delete chain;
    delete chain2;
};