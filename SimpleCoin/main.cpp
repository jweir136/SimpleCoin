#include <iostream>
#include <SimpleCoin/Block/Block.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>
#include <SimpleCoin/Blockchain/Blockchain.hpp>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

int main() {

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
        block.compute_nonce();

        chain.add_block(block.to_json());
    }

    std::cout << chain.verify() << std::endl;
    return (0);
}