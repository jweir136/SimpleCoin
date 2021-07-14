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
        std::size_t size;

        Blockchain() {
            this->size = 0;
            this->hash = 0;
            this->blocks = {};

            this->json_string["blocks"] = this->blocks;
            this->json_string["hash"] = this->hash;
        }

        Blockchain(std::string json_string) {
            this->json_string = json::parse(json_string);
            this->blocks = this->json_string["blocks"];
            this->hash = this->json_string["hash"];
            this->size = this->json_string["size"];
        }

        void add_block(std::string block) {
            this->blocks.push_back(json::parse(block));
            this->hash = std::hash<std::string>()(this->blocks.dump());
            this->size++;

            this->json_string["blocks"] = this->blocks;
            this->json_string["hash"] = this->hash;
            this->json_string["size"] = this->size;
        }

        bool verify() {
            for (int i = 0; i < this->size; i++) {
                auto block = this->json_string["blocks"][i];
                if (((std::size_t)block["hash"] + (unsigned long long)block["nonce"] + (std::size_t)block["last_block"]) % 1000 != 0)
                    return false;
            }

            return true;
        }

        std::string get_block(std::size_t hash) {
            for (int i = 0; i < this->size; i++) {
                auto block = this->json_string["blocks"][i];
                if (block["hash"] == hash)
                    return block.dump();
            }

            return NULL;
        }

        std::string to_json() {
            return this->json_string.dump();
        }
};

#endif