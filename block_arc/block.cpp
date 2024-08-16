#include "block.hpp"
#include "hash_utils.hpp"

// construct block
Block::Block(int idx,                      // init index
             const std::string &hash,      // hash
             const std::string &prev_hash, // previous hash
             const std::vector<std::string>
                 &contents,            // contents of block (transactions)
             const std::string &nonce) // nonce
    : idx(idx), hash(hash), prev_hash(prev_hash), contents(contents),
      nonce(nonce) {
  setMerkleRoot();
}

std::string Block::getHash() const { return hash; }

std::string Block::getPrevHash() const { return prev_hash; }

int Block::getIdx() const { return idx; }

std::vector<std::string> Block::getContents() const { return contents; }

std::string Block::getNonce() const { return nonce; }

// concatenate block and call generate hash for the string
std::string Block::createHash(int idx, const std::string &prev_hash,
                              const std::vector<std::string> &contents,
                              const std::string &nonce) {
  std::string data = std::to_string(idx) + prev_hash + nonce;
  for (const auto &content : contents) {
    data += content;
  }
  return calculateHash(data);
}

// set the Merkle root for the block
void Block::setMerkleRoot() {
  merkleRoot =
      calculateMerkleRoot(contents); // call calculateMerkleRoot from hash_utils
}
std::string Block::getMerkleRoot() const { return merkleRoot; }

// block printing params
void Block::printBlock() const {
  std::cout << "Block #" << idx << "\n";
  std::cout << "Hash: " << hash << "\n";
  std::cout << "Previous Hash: " << prev_hash << "\n";
  std::cout << "Nonce: " << nonce << "\n";
  std::cout << "Contents:\n";
  for (const auto &content : contents) {
    std::cout << " - " << content << "\n";
  }
  std::cout << "Merkle Root: " << merkleRoot << "\n";
}
