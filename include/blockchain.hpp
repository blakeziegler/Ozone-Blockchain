#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <vector>
#include "block.hpp"
#include "proof_of_work.hpp"

class Blockchain {
public:
    Blockchain();
    void addBlock(const std::vector<std::string>& contents);
    bool isValid() const;
    void printBlockchain() const;
    std::vector<Block> chain;
    const std::vector<Block>& getChain() const;

private:
    Block createGenesisBlock() const; // Ensure this declaration matches the definition
    int difficulty;
};

#endif // BLOCKCHAIN_HPP
