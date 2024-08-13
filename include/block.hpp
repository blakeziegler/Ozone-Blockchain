#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "hash_utils.hpp"
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <sys/_types/_time_t.h>
#include <vector>

class Block {
public:
  Block(int idx, const std::string &hash, const std::string &prev_hash,
        const std::vector<std::string> &contents, const std::string &nonce);
  std::string getHash() const;
  std::string getPrevHash() const;
  int getIdx() const;
  std::vector<std::string> getContents() const;
  std::string getNonce() const;
  static std::string createHash(int idx, const std::string &prev_hash,
                                const std::vector<std::string> &contents,
                                const std::string &nonce);
  void setMerkleRoot();
  std::string getMerkleRoot () const;

  void printBlock() const;

  std::string hash;
  std::string nonce;
  time_t timestamp;

private:
  int idx;
  std::string prev_hash;
  std::vector<std::string> contents;
  std::string merkleRoot;
};

#endif // BLOCK_HPP
