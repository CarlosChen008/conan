#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <openssl/sha.h>

class Block {
public:
    std::string previousHash;
    std::string hash;
    std::string data;
    time_t timestamp;

    Block(std::string data, std::string previousHash = "") {
        this->data = data;
        this->previousHash = previousHash;
        this->timestamp = std::time(0);
        this->hash = calculateHash();
    }

    std::string calculateHash() const {
        std::stringstream ss;
        ss << previousHash << timestamp << data;
        std::string input = ss.str();

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)input.c_str(), input.size(), hash);

        std::stringstream hashString;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashString << std::hex << (int)hash[i];
        }

        return hashString.str();
    }
};

class Blockchain {
public:
    Blockchain() {
        chain.push_back(createGenesisBlock());
    }

    void addBlock(Block newBlock) {
        newBlock.previousHash = getLatestBlock().hash;
        newBlock.hash = newBlock.calculateHash();
        chain.push_back(newBlock);
    }

    Block getLatestBlock() const {
        return chain.back();
    }

private:
    std::vector<Block> chain;

    Block createGenesisBlock() const {
        return Block("Genesis Block");
    }
};

int main() {
    Blockchain myBlockchain;

    myBlockchain.addBlock(Block("Block 1 Data"));
    myBlockchain.addBlock(Block("Block 2 Data"));

    for (const auto& block : myBlockchain.chain) {
        std::cout << "Previous Hash: " << block.previousHash << std::endl;
        std::cout << "Data: " << block.data << std::endl;
        std::cout << "Hash: " << block.hash << std::endl;
        std::cout << "Timestamp: " << block.timestamp << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    return 0;
}