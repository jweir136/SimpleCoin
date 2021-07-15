#include <include/catch2/catch.hpp>
#include <SimpleCoin/Block/Block.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>
#include <SimpleCoin/Blockchain/Blockchain.hpp>
#include <iostream>
#include <ctime>
#include <string>

TEST_CASE("mock-blockchain", "[]") {

     Blockchain chain = Blockchain();

    // create the first block.
    {        
        unsigned int amount[3] = { 66, 31, 57 };
        std::string jake = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEvo2EhDT60gPW+8BRq7iB0SkBn+UE\nSOcts5pJSiPb+7uL6jrVQYyyyyVvePXwbMvQBAkl7MuycLry0w9UTEwNDg==\n-----END PUBLIC KEY-----";
        std::string ryan = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEyQQr7BgHRtOB7SJTFbS7i06DX1lo\nQsKDuHIdOmL4z/frRzjdMUuowBH4FyNWDkH51HSxIhZKgxotYR35JAWPPw==\n-----END PUBLIC KEY-----";
        std::string katie = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEHbAzzNc3BXWI619W5W53bmEUlPP6\niO14u4O0GeliUj+U2ZHJ9atbkanpNhtgjoIALYvbM9pBQn2kC/Yb3hTh7Q==\n-----END PUBLIC KEY-----";
        std::string ethan = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEOr1LMSGxb7P3JoCoj/Z4J93C09Mi\nUT5PtVSGWRJRUisRdxJFmVBEB+52T6nY1snpWW9kgQizJcebwaTJtO4yXw==\n-----END PUBLIC KEY-----";

        Tx::TxIn txin = Tx::TxIn(amount[0], 0, 0);
        Tx::TxOut txout = Tx::TxOut(amount[0], ryan);

        Tx::TxIns txins = Tx::TxIns();
        txins.add_txin(txin.to_json());
        Tx::TxOuts txouts = Tx::TxOuts();
        txouts.add_txout(txout.to_json());

        Tx::Transaction jake_to_ryan = Tx::Transaction(txins.to_json(), txouts.to_json(), jake);
        jake_to_ryan.sign_transaction("/Users/jacobweir/projects/cpp/SimpleCoin/test/Cryptography/jake_priv.pem");

        /****************************************************************************************/

        txin = Tx::TxIn(amount[1], 0, 0);
        txout = Tx::TxOut(amount[1], katie);

        txins = Tx::TxIns();
        txins.add_txin(txin.to_json());
        txouts = Tx::TxOuts();
        txouts.add_txout(txout.to_json());

        Tx::Transaction jake_to_katie = Tx::Transaction(txins.to_json(), txouts.to_json(), jake);
        jake_to_katie.sign_transaction("/Users/jacobweir/projects/cpp/SimpleCoin/test/Cryptography/jake_priv.pem");

        /****************************************************************************************/

        txin = Tx::TxIn(amount[2], 0, 0);
        txout = Tx::TxOut(amount[2], ethan);

        txins = Tx::TxIns();
        txins.add_txin(txin.to_json());
        txouts = Tx::TxOuts();
        txouts.add_txout(txout.to_json());

        Tx::Transaction jake_to_ethan = Tx::Transaction(txins.to_json(), txouts.to_json(), jake);
        jake_to_ethan.sign_transaction("/Users/jacobweir/projects/cpp/SimpleCoin/test/Cryptography/jake_priv.pem");

        /****************************************************************************************/

        Block block = Block();
        block.add_transaction(jake_to_ryan.to_json());
        block.add_transaction(jake_to_katie.to_json());
        block.add_transaction(jake_to_ethan.to_json());
        //block.compute_nonce();

        chain.add_block(block.to_json());
    }

    // create the second block.
    {
        unsigned int amount[3] = { 10, 12 };
        std::string jake = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEvo2EhDT60gPW+8BRq7iB0SkBn+UE\nSOcts5pJSiPb+7uL6jrVQYyyyyVvePXwbMvQBAkl7MuycLry0w9UTEwNDg==\n-----END PUBLIC KEY-----";
        std::string ryan = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEyQQr7BgHRtOB7SJTFbS7i06DX1lo\nQsKDuHIdOmL4z/frRzjdMUuowBH4FyNWDkH51HSxIhZKgxotYR35JAWPPw==\n-----END PUBLIC KEY-----";
        std::string katie = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEHbAzzNc3BXWI619W5W53bmEUlPP6\niO14u4O0GeliUj+U2ZHJ9atbkanpNhtgjoIALYvbM9pBQn2kC/Yb3hTh7Q==\n-----END PUBLIC KEY-----";
        std::string ethan = "-----BEGIN PUBLIC KEY-----\nMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEOr1LMSGxb7P3JoCoj/Z4J93C09Mi\nUT5PtVSGWRJRUisRdxJFmVBEB+52T6nY1snpWW9kgQizJcebwaTJtO4yXw==\n-----END PUBLIC KEY-----";
    
        Block last_block = Block(chain.get_index(0));
        Tx::Transaction last_transaction = Tx::Transaction(last_block.get_index(0));

        Tx::TxIn txin = Tx::TxIn(amount[0], last_block.hash, last_transaction.hash);
        Tx::TxOut txout = Tx::TxOut(amount[0], ethan);

        Tx::TxIns txins = Tx::TxIns();
        txins.add_txin(txin.to_json());
        Tx::TxOuts txouts = Tx::TxOuts();
        txouts.add_txout(txout.to_json());

        Tx::Transaction ryan_to_ethan = Tx::Transaction(txins.to_json(), txouts.to_json(), ryan);
        ryan_to_ethan.sign_transaction("/Users/jacobweir/projects/cpp/SimpleCoin/test/Cryptography/ryan_priv.pem");

        /****************************************************************************************/

        last_block = Block(chain.get_index(0));
        last_transaction = Tx::Transaction(last_block.get_index(1));

        txin = Tx::TxIn(amount[1], last_block.hash, last_transaction.hash);
        txout = Tx::TxOut(amount[1], ethan);

        txins = Tx::TxIns();
        txins.add_txin(txin.to_json());
        txouts = Tx::TxOuts();
        txouts.add_txout(txout.to_json());

        Tx::Transaction katie_to_ethan = Tx::Transaction(txins.to_json(), txouts.to_json(), katie);
        katie_to_ethan.sign_transaction("/Users/jacobweir/projects/cpp/SimpleCoin/test/Cryptography/katie_priv.pem");

        /****************************************************************************************/

        Block block = Block();
        block.add_transaction(ryan_to_ethan.to_json());
        block.add_transaction(katie_to_ethan.to_json());

        chain.add_block(block.to_json());
    }

    chain.get_index(0);
};

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