#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <functional>
#include <string>
#include <bitset>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <ctime>
#include <regex>
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
}

#endif