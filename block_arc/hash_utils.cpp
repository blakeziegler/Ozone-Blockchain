#include "hash_utils.hpp"
#include "block.hpp"
#include <cstddef>
#include <iomanip>
#include <openssl/bio.h>
#include <openssl/cryptoerr_legacy.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <sstream>
#include <stdexcept>
#include <string>

// calculate hash from string
std::string calculateHash(const std::string &data) {
  unsigned char hash[EVP_MAX_MD_SIZE]; // buffer array
  unsigned int hash_len;               // store hash len
  
  // EVP digest
  // message -> cryptographic hash 
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new(); // new context
  if (mdctx == nullptr) {
    throw std::runtime_error("Failed to create EVP_MD_CTX, *NULL*");
  }
  
  // initalize digest context w/ SHA hash
  if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) { // nullptr = placeholder for special engine
    EVP_MD_CTX_free(mdctx); // free mem if != 1
    throw std::runtime_error("Failed to initialize digest");
  }
  
  // add data repeat call
  if (EVP_DigestUpdate(mdctx, data.c_str(), data.size()) != 1) { // ptr to string data at length of data
    EVP_MD_CTX_free(mdctx);
    throw std::runtime_error("Failed to update digest");
  }
  
  // digest -> calculation -> write into buffer -> free digest
  if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) != 1) {
    EVP_MD_CTX_free(mdctx);
    throw std::runtime_error("Failed to complete digest");
  }

  EVP_MD_CTX_free(mdctx);
  
  // make data readable
  std::stringstream ss;
  for (unsigned int i = 0; i < hash_len; ++i) {
    ss << std::hex << std::setw(2) << std::setfill('0')
       << static_cast<int>(hash[i]);
  }

  return ss.str();
}

// Private key
std::string signData(const std::string &privateKey, const std::string &data) {
  EVP_PKEY *pkey = nullptr; // initalize at empty
  BIO *bio = // create memory buff for key string
      BIO_new_mem_buf(privateKey.data(), static_cast<int>(privateKey.size()));
  PEM_read_bio_PrivateKey(bio, &pkey, nullptr, nullptr); // read key
  BIO_free(bio); // free memory

  if (!pkey) {
    throw std::runtime_error("Failed to load private key");
  }
  // follow same system as hash
  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  if (!mdctx) {
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to create EVP_MD_CTX");
  }

  if (EVP_DigestSignInit(mdctx, nullptr, EVP_sha256(), nullptr, pkey) != 1) {
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to initialize digest sign");
  }

  if (EVP_DigestSignUpdate(mdctx, data.data(), data.size()) != 1) {
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to update digest sign");
  }

  size_t siglen = 0;
  if (EVP_DigestSignFinal(mdctx, nullptr, &siglen) != 1) {
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to finalize digest sign (get length)");
  }

  std::vector<unsigned char> sig(siglen);
  if (EVP_DigestSignFinal(mdctx, sig.data(), &siglen) != 1) {
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to finalize digest sign");
  }

  EVP_MD_CTX_free(mdctx);
  EVP_PKEY_free(pkey);

  return std::string(reinterpret_cast<char *>(sig.data()), siglen);
}

// Verifying the signature
bool verifySignature(const std::string &publicKey, const std::string &data,
                     const std::string &signature) {
  EVP_PKEY *pkey = nullptr;
  BIO *bio =
      BIO_new_mem_buf(publicKey.data(), static_cast<int>(publicKey.size()));
  PEM_read_bio_PUBKEY(bio, &pkey, nullptr, nullptr);
  BIO_free(bio);

  if (!pkey) {
    throw std::runtime_error("Failed to load public key");
  }

  EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
  if (!mdctx) {
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to create EVP_MD_CTX");
  }

  if (EVP_DigestVerifyInit(mdctx, nullptr, EVP_sha256(), nullptr, pkey) != 1) {
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to initialize digest verify");
  }

  if (EVP_DigestVerifyUpdate(mdctx, data.data(), data.size()) != 1) {
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    throw std::runtime_error("Failed to update digest verify");
  }

  bool verified =
      EVP_DigestVerifyFinal(
          mdctx, reinterpret_cast<const unsigned char *>(signature.data()),
          signature.size()) == 1;

  EVP_MD_CTX_free(mdctx);
  EVP_PKEY_free(pkey);

  return verified;
}

// merkleroot: unique hash for all transactions in a block
std::string calculateMerkleRoot(const std::vector<std::string> &contents) {
  if (contents.empty()) {
    return "";
  }

  // merkle leaves
  std::vector<std::string> currContents = contents;
  while (currContents.size() > 1) {
    if (currContents.size() % 2 != 0) {
      currContents.push_back(currContents.back()); // duplicate last if odd (needs to be in pairs)
    }

    std::vector<std::string> nextContents;
    for (size_t i = 0; i < currContents.size(); i += 2) {
      std::string combinedHash =
          calculateHash(currContents[i] + currContents[i + 1]);
      nextContents.push_back(combinedHash);
    }

    currContents = nextContents; // move depth
  }

  return currContents[0];
}
