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
    std::string reciever = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEkculYE8/uBwUC8tST0DTZ0bWQ+gi\nOdsPVDp0t4657MyHvwZIIh9giKvNYcF0uuw3hrMBpX2nESD8ypdiUNlgDg==\n-----END PUBLIC KEY-----";
    std::string author = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEkculYE8/uBwUC8tST0DTZ0bWQ+gi\nOdsPVDp0t4657MyHvwZIIh9giKvNYcF0uuw3hrMBpX2nESD8ypdiUNlgDg==\n-----END PUBLIC KEY-----";

    Tx::TxOuts* txouts = new Tx::TxOuts();

    unsigned long block;
    unsigned long tx;

    Tx::TxIns* txins = new Tx::TxIns();

    Tx::Transaction* trans;
    Block* blockobj = new Block();
    Blockchain* chain = new Blockchain();
    Blockchain* chain2;

    for (int i = 0; i < 10; i++) {
        amount = rand() % 1000;

        txouts->add_txout(amount, reciever);

        block = rand() % 1000;
        tx = rand() % 1000;

        txins->add_txin(amount, block, tx);

        trans = new Tx::Transaction(txins->to_json(), txouts->to_json(), author);
        blockobj->add_transaction(trans->to_json());

        chain->add_block(blockobj->to_json());

        chain2 = new Blockchain(chain->to_json());

        REQUIRE(chain->json_string == chain2->json_string);
        REQUIRE(chain->get_block(blockobj->hash) == blockobj->to_json());
    }

    REQUIRE(!chain->verify());

    delete txins;
    delete txouts;
    delete trans;
    delete blockobj;
    delete chain;
    delete chain2;
};