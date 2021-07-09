#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <cmath>
#include <include/json/json.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>

using namespace nlohmann;

class Blockchain {
    public:
        json        json_string;
        json        blocks;
        std::size_t hash;

        Blockchain() {
            this->hash = 0;
            this->blocks = {};

            this->json_string["blocks"] = this->blocks;
            this->json_string["hash"] = this->hash;
        }

        Blockchain(std::string json_string) {
            this->json_string = json::parse(json_string);
            this->blocks = this->json_string["blocks"];
            this->hash = this->json_string["hash"];
        }

        void add_block(std::string block) {
            this->blocks.push_back(json::parse(block));
            this->hash = std::hash<std::string>()(this->blocks.dump());

            this->json_string["blocks"] = this->blocks;
            this->json_string["hash"] = this->hash;
        }

        bool verify() {

        }

        std::string json() {
            return this->json_string.dump();
        }
};

#endif