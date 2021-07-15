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
        std::size_t size;
        json        hashes;

        Blockchain() {
            this->size = 0;
            this->hashes = {};

            this->json_string["hashes"] = this->hashes;
            this->json_string["size"] = this->size;
        }

        Blockchain(std::string json_string) {
            this->json_string = json::parse(json_string);

            this->size = this->json_string["size"];
            this->hashes = this->json_string["hashes"];
        }

        void add_block(std::string block) {
            std::size_t block_hash = json::parse(block)["hash"];
            this->hashes.push_back(block_hash);
            this->json_string["blocks"][std::to_string(block_hash)] = block;
            this->size++;

            this->json_string["size"] = this->size;
            this->json_string["hashes"] = this->hashes;
        }

        bool verify() {
            for (std::size_t current_hash : this->json_string["hashes"]) {
                Block* current_block = new Block(this->json_string["blocks"][std::to_string(current_hash)]);

                std::cout << current_block->is_nonce_valid() << std::endl;

                if (!current_block->is_valid() || !current_block->is_nonce_valid())
                    return false;

                delete current_block;
            }

            return true;
        }

        std::string get_block(std::size_t hash) {
            return this->json_string["blocks"][std::to_string(hash)];
        }

        std::string get_index(std::size_t index) {
            std::size_t hash = this->json_string["hashes"][index];
            std::string selected_block = this->json_string["blocks"][std::to_string(hash)];
            
            return selected_block;
        }

        std::string to_json() {
            return this->json_string.dump();
        }
};

#endif