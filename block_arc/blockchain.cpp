#include "blockchain.hpp"
#include "hash_utils.hpp"
#include "proof_of_work.hpp"

Blockchain::Blockchain() : difficulty(4) { // arbitrary difficulty
  chain.push_back(createGenesisBlock());
}
// genesis block
Block Blockchain::createGenesisBlock() const {
  return Block(0, Block::createHash(0, "0", {"Genesis Block"}, "0"), "0",
               {"Genesis Block"}, "0");
}

// adding block to chain
void Blockchain::addBlock(
    const std::vector<std::string>
        &contents) {                     // vector -> string at address contents
  const Block &lastBlock = chain.back(); // fetch last block
  int newIndex = lastBlock.getIdx() + 1; // set new block idx
  Block newBlock(newIndex, "", lastBlock.getHash(), contents,
                 "0"); // fetch last hash
  ProofOfWork::mineBlock(newBlock, difficulty);
  chain.push_back(newBlock); // set new block as current block after pow
}
// chain validation
bool Blockchain::isValid() const {
  // iterate through chain
  for (size_t i = 1; i < chain.size(); ++i) {

    // hash match
    const Block &currentBlock = chain[i];
    const Block &previousBlock = chain[i - 1];
    if (currentBlock.getHash() != Block::createHash(currentBlock.getIdx(),
                                                    currentBlock.getPrevHash(),
                                                    currentBlock.getContents(),
                                                    currentBlock.getNonce())) {
      return false;
    }

    if (currentBlock.getPrevHash() != previousBlock.getHash()) {
      return false;
    }
  }
  return true;
}

// print out
void Blockchain::printBlockchain() const {
  for (const auto &block : chain) {
    block.printBlock();
    std::cout << std::endl;
  }
}

const std::vector<Block> &Blockchain::getChain() const { return chain; }
