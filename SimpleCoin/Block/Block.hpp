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
        std::size_t         hash;
        unsigned long long  nonce;
        bool                empty;
        json                json_string;
        std::size_t         last_block;
        json                hashes;

        Block() {
            this->epoch = time(NULL);
            this->hash = 0;
            this->nonce = 0;
            this->empty = true;
            this->last_block = 0;
            this->hashes = {};
            
            this->json_string["last_block"] = this->last_block;
            this->json_string["time"] = this->epoch;
            this->json_string["hash"] = this->hash;
            this->json_string["nonce"] = this->nonce;
            this->json_string["hashes"] = this->hashes;
        }

        Block(std::string json_string) {
            this->json_string = json::parse(json_string);
            this->empty = false;
            
            this->last_block = this->json_string["last_block"];
            this->epoch = this->json_string["time"];
            this->hash = this->json_string["hash"];
            this->nonce = this->json_string["nonce"];
            this->hashes = this->json_string["hashes"];
        }

        void add_transaction(std::string transaction_json) {
            std::size_t transaction_hash = json::parse(transaction_json)["hash"];
            this->json_string["transactions"][std::to_string(transaction_hash)] = transaction_json;
            this->hashes.push_back(transaction_hash);
            this->hash = compute_hash();
            this->json_string["hash"] = this->hash;
            this->json_string["hashes"] = this->hashes;
        }

        void compute_nonce() {
            std::size_t current_hash = std::hash<std::string>()(std::to_string(this->last_block) + std::to_string(this->hash) + std::to_string(this->nonce));
            while (current_hash % 1000 != 0)
                this->nonce = rand() % 0xffffffffffffffff;
        }

        std::string to_json() {
            this->json_string["hash"] = compute_hash();

            return this->json_string.dump();
        }

        std::string get_transaction(std::string hash) {
            return this->json_string["transactions"][hash];
        }

        bool is_nonce_valid() {
            return std::hash<std::string>()(std::to_string(this->last_block) + std::to_string(this->hash) + std::to_string(this->nonce)) % 1000 == 0;
        }

        bool is_valid() {
            for (std::size_t current_hash : this->json_string["hashes"]) {
                Tx::Transaction*  current_transaction = new Tx::Transaction(this->json_string["transactions"][std::to_string(current_hash)]);

                if (!current_transaction->is_balanced() || !current_transaction->verify_transaction())
                    return false;

                delete current_transaction;
            }

            return true;
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