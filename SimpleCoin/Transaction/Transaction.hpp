#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <functional>
#include <string>
#include <bitset>
#include <iostream>
#include <cmath>
#include <stdexcept>

namespace Tx {
    class TxIn {
        public:
            unsigned long block;
            unsigned long tx;
            unsigned int  amount;
            std::size_t   hash;
            std::bitset<16*sizeof(unsigned long) + 8*sizeof(std::size_t) + 8*sizeof(unsigned int)> bits;

            TxIn() {
                // SET ALL THE NULL
                this->block = 0;
                this->tx = 0;
                this->amount = 0;
                this->hash = 0;    
            }

            TxIn(const unsigned long block, const unsigned long tx, const unsigned int amount) {
                this->block = block;
                this->tx = tx;
                this->amount = amount;
                this->hash = get_hash();

                std::string block_bits = std::bitset<8*sizeof(unsigned long)>(this->block).to_string();
                for (int i = 0; i < block_bits.length(); i++)
                    if (block_bits[i] == '1')
                        this->bits.set(i);

                std::string tx_bits = std::bitset<8*sizeof(unsigned long)>(this->tx).to_string();
                for (int i = 0; i < tx_bits.length(); i++)
                    if (tx_bits[i] == '1')
                        this->bits.set(8*sizeof(unsigned long) + i);

                std::string hash_bits = std::bitset<8*sizeof(std::size_t)>(this->hash).to_string();
                for (int i = 0; i < hash_bits.length(); i++)
                    if (hash_bits[i] == '1')
                        this->bits.set(16*sizeof(unsigned long) + i);

                std::string amount_bits = std::bitset<8*sizeof(unsigned int)>(this->amount).to_string();
                for (int i = 0; i < amount_bits.length(); i++)
                    if (amount_bits[i] == '1')
                        this->bits.set(16*sizeof(unsigned long) + 8*sizeof(std::size_t) + i);
            }

            TxIn(const std::string bits) {
                this->bits = std::bitset<16*sizeof(unsigned long) + 8*sizeof(std::size_t) + 8*sizeof(unsigned int)>(bits);

                std::bitset<8*sizeof(unsigned int)> amount_bits = std::bitset<8*sizeof(unsigned int)>(reverse(bits.substr(0,8*sizeof(unsigned int))));
                this->amount = amount_bits.to_ulong();

                std::bitset<8*sizeof(unsigned long)> tx_bits = std::bitset<8*sizeof(unsigned long)>(reverse(bits.substr(8*sizeof(unsigned long)+8*sizeof(unsigned int),8*sizeof(unsigned long))));
                this->tx = tx_bits.to_ulong();

                std::bitset<8*sizeof(unsigned long)> block_bits = std::bitset<8*sizeof(unsigned long)>(reverse(bits.substr(16*sizeof(unsigned long)+8*sizeof(unsigned int),8*sizeof(unsigned long))));
                this->block = block_bits.to_ulong();

            }

            friend std::ostream& operator<<(std::ostream& os, const TxIn& tx) {
                os << tx.bits.to_string();
                return os;
            }

            std::string serialize() {
                return this->bits.to_string();
            }

        private:
            std::size_t get_hash() {
                std::size_t block_hash = std::hash<unsigned long>()(this->block);
                std::size_t tx_hash = std::hash<unsigned long>()(this->tx);
                std::size_t amount_hash = std::hash<unsigned int>()(this->amount);

                return (block_hash ^ (tx_hash << 1)) ^ (amount_hash << 1);
            }

            std::string reverse(std::string str) {
                    std::string result = "";
                    for (int i = str.length()-1; i >= 0; i--)
                        result += str[i];
                    return result;
            }
    };

    class TxIns {
        public:
            Tx::TxIn* txins;
            std::size_t size;
            std::size_t* hashes;

            TxIns() {
                this->txins = new Tx::TxIn[5];
                this->size = 0;
                this->hashes = new std::size_t[5];
            }

            void add_txin(const unsigned long block, const unsigned long tx, const unsigned int amount) {
                if (this->size >= 5)
                    throw std::logic_error("Error: Maximum Number of TxIn Transactions Added. Cannot add anymore.");
                
                this->txins[this->size] = Tx::TxIn(block, tx, amount);
                this->hashes[this->size] = this->txins[this->size].hash;

                this->size++;
            }

            void add_txin(const std::string bits) {
                if (this->size >= 5)
                    throw std::logic_error("Error: Maximum Number of TxIn Transactions Added. Cannot add anymore.");
                
                this->txins[this->size] = Tx::TxIn(bits);
                this->hashes[this->size] = this->txins[this->size].hash;

                this->size++;
            }
    };
}

#endif