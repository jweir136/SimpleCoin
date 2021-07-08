#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <include/json/json.hpp>

using namespace nlohmann;

namespace Tx {
    class TxIn {
        public:
            unsigned int    amount;
            unsigned long   block;
            unsigned long   tx;
            json            json_string;

            TxIn(unsigned int amount, unsigned long block, unsigned long tx) {
                this->amount = amount;
                this->block = block;
                this->tx = tx;

                this->json_string["amount"] = amount;
                this->json_string["block"] = block;
                this->json_string["tx"] = tx;
            }

            TxIn(std::string json_string) {
                this->json_string = json::parse(json_string);

                this->amount = this->json_string["amount"];
                this->block = this->json_string["block"];
                this->tx = this->json_string["tx"];
            }

            std::string json() {
                return this->json_string.dump();
            }
    };

    class TxIns {
        public:
            json txins;

            TxIns() {
                this->txins = {};
            }

            TxIns(std::string json_string) {
                this->txins = json::parse(json_string);
            }

            void add_txin(unsigned int amount, unsigned long block, unsigned long tx) {
                Tx::TxIn txin = Tx::TxIn(amount, block, tx);
                this->txins.push_back(txin.json());
            }

            void add_txin(std::string json_string) {
                this->txins.push_back(json_string);
            }

            std::string json() {
                return this->txins.dump();
            }
    };

    class TxOut {
        public:
            unsigned int    amount;
            unsigned long   reciever;
            json            json_string;

            TxOut(unsigned int amount, unsigned long reciever) {
                this->amount = amount;
                this->reciever = reciever;

                this->json_string["amount"] = amount;
                this->json_string["reciever"] = reciever;
            }

            TxOut(std::string json_string) {
                this->json_string = json::parse(json_string);

                this->amount = this->json_string["amount"];
                this->reciever = this->json_string["reciever"];
            }

            std::string json() {
                return this->json_string.dump();
            }
    };

    class TxOuts {
        public:
            json txouts;

            TxOuts() {
                this->txouts = {};
            }

            TxOuts(std::string json_string) {
                this->txouts = json::parse(json_string);
            }

            void add_txout(unsigned int amount, unsigned long reciever) {
                Tx::TxOut txout = Tx::TxOut(amount, reciever);
                this->txouts.push_back(txout.json());
            }

            void add_txout(std::string json_string) {
                this->txouts.push_back(json_string);
            }

            std::string json() {
                return this->txouts.dump();
            }
    };

    class Transaction {
        public:
            std::size_t     hash;
            unsigned long   epoch;
            json            txins;
            json            txouts;
            json            json_string;

            Transaction(std::string txins, std::string txouts) {
                this->epoch = time(NULL);
                this->txins = json::parse(txins);
                this->txouts = json::parse(txouts);

                this->json_string["time"] = this->epoch;
                this->json_string["txins"] = this->txins;
                this->json_string["txouts"] = this->txouts;

                this->hash = std::hash<std::string>()(this->json_string.dump());

                this->json_string["hash"] = this->hash;
            }    

            Transaction(std::string json_string) {
                this->json_string = json::parse(json_string);
                
                this->epoch = this->json_string["time"];
                this->txins = this->json_string["txins"];
                this->txouts = this->json_string["txouts"];
                this->hash = this->json_string["hash"];
            }  

            std::string json() {
                return this->json_string.dump();
            }   
    };
}

#endif