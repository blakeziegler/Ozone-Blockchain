#include "block.hpp"
#include "blockchain.hpp"
#include "hash_utils.hpp"
#include "nlohmann/json_fwd.hpp"
#include "proof_of_work.hpp"
#include "transaction.hpp"
#include "ipfs_utils.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <string>


// Example keys
const std::string privateKey = R"(-----BEGIN ENCRYPTED PRIVATE KEY-----
*****COPY KEY HERE******
-----END ENCRYPTED PRIVATE KEY-----)";
const std::string publicKey = R"(-----BEGIN PUBLIC KEY-----
*****COPY KEY HERE******
-----END PUBLIC KEY-----)";

nlohmann::json block_to_json(const Block &block) {
    return {
        {"index", block.getIdx()},
        {"hash", block.getHash()},
        {"previous_hash", block.getPrevHash()},
        {"nonce", block.getNonce()},
        {"contents", block.getContents()},
        {"merkle_root", block.getMerkleRoot()},
    };
}
int main() {
  try {
    Blockchain blockchain;

    // test transactions
    std::string data1 = "Alice->Bob:10";
    std::string data2 = "Bob->Charlie:5";

    std::string signature1 = signData(privateKey, data1);
    std::string signature2 = signData(privateKey, data2);

    std::cout << "Data 1: " << data1 << std::endl;
    std::cout << "Signature 1: " << signature1 << std::endl;
    std::cout << "Data 2: " << data2 << std::endl;
    std::cout << "Signature 2: " << signature2 << std::endl;

    // Verify before adding to the blockchain
    if (verifySignature(publicKey, data1, signature1) &&
        verifySignature(publicKey, data2, signature2)) {

      // Add blocks with the signed transactions
      blockchain.addBlock({data1, data2});
    } else {
      std::cerr << "Transaction verification failed!" << std::endl;
      return 1;
    }

    // Add another block with different transactions
    std::string data3 = "Charlie->Dave:7.5";
    std::string data4 = "Dave->Eve:2.5";

    std::string signature3 = signData(privateKey, data3);
    std::string signature4 = signData(privateKey, data4);

    std::cout << "Data 3: " << data3 << std::endl;
    std::cout << "Signature 3: " << signature3 << std::endl;
    std::cout << "Data 4: " << data4 << std::endl;
    std::cout << "Signature 4: " << signature4 << std::endl;

    if (verifySignature(publicKey, data3, signature3) &&
        verifySignature(publicKey, data4, signature4)) {

      blockchain.addBlock({data3, data4});
    } else {
      std::cerr << "Transaction verification failed!" << std::endl;
      return 1;
    }

    // Print the blockchain
    blockchain.printBlockchain();
    // iterate through chain and extract Merkle root of current block index
    for (size_t i = 0; i < blockchain.chain.size(); ++i) {
      const Block &block = blockchain.chain[i];
      std::cout << "Merkle Root for Block #" << block.getIdx() << ": "
                << block.getMerkleRoot() << std::endl;
      // dump block to json, upload to ipfs with hash
      nlohmann::json block_json = block_to_json(block);
      std::string block_data = block_json.dump();
      std::string ipfs_hash = ipfs_upload(block_data);
    }

    // Validate the blockchain
    if (blockchain.isValid()) {
      std::cout << "Blockchain is valid." << std::endl;
    } else {
      std::cout << "Blockchain is invalid!" << std::endl;
    }

  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}



