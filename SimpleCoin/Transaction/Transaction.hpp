#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <include/json/json.hpp>
#include <SimpleCoin/Cryptography/crypto.hpp>

using namespace nlohmann;

namespace Tx {
    /**
     * @brief TxIn represents the input for a Transaction. This object points to a previous Transaction and tells the
     * transaction where the tokens that are being spent comes from.
     */
    class TxIn {
        public:
            unsigned int    amount;
            unsigned long   block;
            unsigned long   tx;
            json            json_string;

            /**
             * @brief Creates a new TxIn instance using the given amount, block, and tx.
             * @param amount The amount to take from the selected Transaction.
             * @param block  The address of the block where the selected Transaction can be found.
             * @param tx    The address of the Transaction being selected.
             */
            TxIn(unsigned int amount, unsigned long block, unsigned long tx) {
                this->amount = amount;
                this->block = block;
                this->tx = tx;

                this->json_string["amount"] = amount;
                this->json_string["block"] = block;
                this->json_string["tx"] = tx;
            }

            /**
             * @brief Creates a new TxIn instance using a serialized TxIn instance.
             * @param json_string This is the json string to use to initialize the instance. This should be from a serialized TxIn instance.
             */ 
            TxIn(std::string json_string) {
                this->json_string = json::parse(json_string);

                this->amount = this->json_string["amount"];
                this->block = this->json_string["block"];
                this->tx = this->json_string["tx"];
            }

            /**
             * @brief Returns the json data from the instance. This is to be used to store, transfer, and serialize TxIn object.
             * @return Returns the json data in string format.
             */ 
            std::string to_json() {
                return this->json_string.dump();
            }
    };

    /**
     * @brief TxIns is a basic object used to store one or more TxIn objects. This object is meant to allow Transaction object to take their inputed token from more than one source.
     */ 
    class TxIns {
        public:
            json            json_string;
            unsigned long   total;

            /**
             * @brief Creates an empty TxIns object.
             */
            TxIns() {
                this->json_string["txins"] = {};
                this->total = 0;
                this->json_string["total"] = this->total;
            }

            /**
             * @brief Creates a TxIns object from a json string. The json string should be the serialized format of another TxIns object.
             * @param json_string The json data to use to initialize the object.
             */ 
            TxIns(std::string json_string) {
                this->json_string = json::parse(json_string);
                this->total = this->json_string["total"];
            }

            /**
             * @brief Creates a new TxIn instance using the given data and adds it to the TxIns instance.
             * @param amount The number of tokens to use in the transaction input.
             * @param block The address of the block where the input Transaction can be found.
             * @param tx The address of the inputed Transaction.
             */ 
            void add_txin(unsigned int amount, unsigned long block, unsigned long tx) {
                Tx::TxIn txin = Tx::TxIn(amount, block, tx);
                this->json_string["txins"].push_back(txin.to_json());
                this->total += amount;
                this->json_string["total"] = this->total;
            }

            /**
             * @brief Creates a new TxIn instance from the given json data. The json data should correspond to a TxIn object.
             * @param json_string The json data from the TxIn object.
             */ 
            void add_txin(std::string json_string) {
                this->json_string["txins"].push_back(json_string);
                this->total += (unsigned long)this->json_string["total"];
                this->json_string["total"] = this->total;
            }

            /**
             * @brief Returns a json serialization of the TxIns object. This is mostly just a list of the TxIn objects.
             * @return Returns the json data in string format.
             */ 
            std::string to_json() {
                return this->json_string.dump();
            }
    };

    /**
     * @brief TxOut represents the output for a Transaction. This tells the Transaction where to send the tokens being used.
     */
    class TxOut {
        public:
            unsigned int    amount;
            std::string     reciever;
            json            json_string;

            /**
             * @brief Initializes a TxOut instance using the given amount and reciever.
             * @param amount This is the number of tokens to give to the reciever.
             * @param reciever This is the public key of the user to give tokens to.
             */ 
            TxOut(unsigned int amount, std::string reciever) {
                this->amount = amount;
                this->reciever = reciever;

                this->json_string["amount"] = amount;
                this->json_string["reciever"] = reciever;
            }

            /**
             * @brief Initializes a TxOut object using the json data from another TxOut object.
             * @param json_string This is json data to use to initiaize the object.
             */
            TxOut(std::string json_string) {
                this->json_string = json::parse(json_string);

                this->amount = this->json_string["amount"];
                this->reciever = this->json_string["reciever"];
            }

            /**
             * @brief Returns the json data to the TxOut object.
             * @return Returns a string representing the JSON data.
             */
            std::string to_json() {
                return this->json_string.dump();
            }
    };

    /**
     * @brief TxOuts is an object used to store one or more TxOut objects. This object allows Transaction objects to send tokens to more than one user in a single transaction.
     */
    class TxOuts {
        public:
            json            json_string;
            unsigned long   total;

            /**
             * @brief Initialize an empty TxOuts object containing no TxOut objects.
             */
            TxOuts() {
                this->json_string["txouts"] = {};
                this->total = 0;
                this->json_string["total"] = this->total;
            }

            /**
             * @brief Initialize a TxOuts object from the JSON data from another TxOuts object.
             * @param json_string This is the JSON data to use to initialize the object.
             */
            TxOuts(std::string json_string) {
                this->json_string = json::parse(json_string);
                this->total = this->json_string["total"];
            }

            /**
             * @brief Add a new TxOut object to the TxOuts instance using the given data.
             * @param amount This is the number of tokens to send to the reciever.
             * @param reciever This is the public key belonging to the user the tokens should be sent to.
             */
            void add_txout(unsigned int amount, std::string reciever) {
                Tx::TxOut txout = Tx::TxOut(amount, reciever);
                this->json_string["txouts"].push_back(txout.to_json());
                this->total += amount;
                this->json_string["total"] = this->total;
            }

            /**
             * @brief Add a new TxOut object to the TxOuts instance using the JSON data from another TxOut instance.
             * @param json_string This is the JSON data representing a serialized TxOut instance.
             */
            void add_txout(std::string json_string) {
                this->json_string["txouts"].push_back(json_string);
                this->total += (unsigned long)json::parse(json_string)["amount"];
            }

            /**
             * @brief Serializes the TxOuts data and returns the JSON data.
             * @return Returns the JSON data corresponding to the TxOuts object.
             */
            std::string to_json() {
                return this->json_string.dump();
            }
    };

    /**
     * @brief A Transaction is the most important object in the Tx namespace. It represents a single Transaction and is used to transfer tokens from one public key to another.
     * A Transaction contains four components: time, txins, txouts, and the hash. In order for a Transaction to be considered valid the number of tokens inputed to the transaction and the number of tokens being outputed by the Transaction must be the same.
     */
    class Transaction {
        public:
            std::string     author_key;
            std::string     signature;
            std::size_t     hash;
            unsigned long   epoch;
            json            txins;
            json            txouts;
            json            json_string;

            /**
             * @brief Initialize a Transaction using the JSON data from both a TxIns object and a TxOuts object.
             * @param txins This is the JSON data for a TxIns object, the inputed tokens.
             * @param txouts This is the JSON data for a TxOuts object, the output locations of the tokens.
             * @param author_key This is the PEM string for the public key of the user writing this Transaction.
             */
            Transaction(std::string txins, std::string txouts, std::string author_key) {
                this->epoch = time(NULL);
                this->txins = json::parse(txins);
                this->txouts = json::parse(txouts);
                this->author_key = author_key;
                this->signature = "";

                this->json_string["time"] = this->epoch;
                this->json_string["txins"] = this->txins;
                this->json_string["txouts"] = this->txouts;
                this->json_string["author_key"] = this->author_key;
                this->json_string["signature"] = this->signature;

                this->hash = std::hash<std::string>()(this->json_string.dump());

                this->json_string["hash"] = this->hash;
            }    

            /**
             * @brief Initialize a Transaction using the JSON data from another serialized Transaction object.
             * @param json_string This is the JSON data from a serialized Transaction object to use to initialize the object.
             */
            Transaction(std::string json_string) {
                this->json_string = json::parse(json_string);
                
                this->epoch = this->json_string["time"];
                this->txins = this->json_string["txins"];
                this->txouts = this->json_string["txouts"];
                this->hash = this->json_string["hash"];
                this->author_key = this->json_string["author_key"];
                this->signature = this->json_string["signature"];
            }  

            /**
             * @brief Serializes the Transaction object and returns the JSON data as a string.
             * @return Returns a string representing the serialized Transaction object.
             */
            std::string to_json() {
                return this->json_string.dump();
            }   

            void sign_transaction(std::string private_key_filepath) {
                /*
                    ERROR SIGNATURE : DOESN'T HAVE 
                */
                this->signature = ECDSA::sign(private_key_filepath, std::to_string(this->hash));
                std::u32string s32(this->signature.begin(), this->signature.end());
                this->json_string["signature"] = s32;
            }

            bool verify_transaction() {
                return ECDSA::verify_from_string(this->author_key, std::to_string(this->hash), this->signature);
            }

            bool is_balanced() {
                return (unsigned long)this->txins["total"] == (unsigned long)this->txouts["total"];
            }
    };
}

#endif