#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <cmath>
#include <include/json/json.hpp>
#include <SimpleCoin/Transaction/Transaction.hpp>

using namespace nlohmann;

class Block {
    public:
        unsigned long       epoch;
        json                transactions;
        std::size_t         hash;
        unsigned long long  nonce;
        bool                empty;
        json                json_string;
        std::size_t         last_block;

        Block() {
            this->epoch = time(NULL);
            this->transactions = {};
            this->hash = 0;
            this->nonce = 0;
            this->empty = true;
            this->last_block = 0;
            
            this->json_string["last_block"] = this->last_block;
            this->json_string["time"] = this->epoch;
            this->json_string["hash"] = this->hash;
            this->json_string["nonce"] = this->nonce;
            this->json_string["transactions"] = this->transactions;

        }

        Block(std::string json_string) {
            this->json_string = json::parse(json_string);
            this->empty = false;
            
            this->last_block = this->json_string["last_block"];
            this->epoch = this->json_string["time"];
            this->hash = this->json_string["hash"];
            this->nonce = this->json_string["nonce"];
            this->transactions = this->json_string["transactions"];
        }

        void add_transaction(std::string transaction_json) {
            this->json_string["transactions"].push_back(transaction_json);
            this->hash = compute_hash();
            this->json_string["hash"] = this->hash;
        }

        void compute_nonce() {
            while ((this->last_block + this->hash + this->nonce) % 1000 != 0) {
                this->nonce = rand() % 0xffffffffffffffff;
            }
        }

        std::string json() {
            this->json_string["hash"] = compute_hash();

            return this->json_string.dump();
        }

    private:
        std::size_t compute_hash() {
            std::string epoch_string = std::to_string(this->epoch);
            std::string nonce_string = std::to_string(this->nonce);
            std::string last_block_string = std::to_string(this->last_block);
            std::string trans_hash = this->json_string["transactions"].dump();

            return std::hash<std::string>()(last_block_string + epoch_string + nonce_string + trans_hash);
        }
};


#endif