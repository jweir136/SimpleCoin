#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <include/json/json.hpp>

using namespace nlohmann;

namespace Tx {
    class TxIn {
        public:
            unsigned int    amount;
            unsigned long   block;
            unsigned long   tx;
            json      json_string;

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
}

#endif