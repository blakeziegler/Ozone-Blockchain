#ifndef HASH_UTILS_HPP
#define HASH_UTILS_HPP

#include <string>
#include <vector>

// Function to calculate the hash of a block
std::string calculateHash(const std::string &data);

// Function to sign data
std::string signData(const std::string& privateKey, const std::string& data);

// Function to verify a signature
bool verifySignature(const std::string& publicKey, const std::string& data, const std::string& signature);

// merkle root
std::string calculateMerkleRoot(const std::vector<std::string> &contents);
#endif // HASH_UTILS_HPP
