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
MIIFLTBXBgkqhkiG9w0BBQ0wSjApBgkqhkiG9w0BBQwwHAQIxVwTxlHF+KcCAggA
MAwGCCqGSIb3DQIJBQAwHQYJYIZIAWUDBAEqBBBSeg9NgDHn/XICj9kXRGteBIIE
0LvJEXU4NI7EQHnV0tIX1RwWxdfCyjaT/PAbc/H5X6zWDJKU2BEtx5lG/FpPrOr9
lWUGYHSmerCWBOoZBOMQwBEv5L+HvX44CcLw0OjE70RLZO6m3GxN3m8QwnAHPPXR
7BHzP6P/Ajkvche2t1+J4zH0+H2o9K5zRUxhAMRnju83ARO2iASav3xU3NqvQSKo
3+oi53URLySnvXYvAQaoSgeiHJqyjjzpYcQRRJwOnIzuRjBq/fbiXS3qT0ZtFz9q
NXCzg4tBxEIRSvh51Cynm8oGGXZSE6mqu3EKv48JG90o8lXfIU4NVDTf7Scs80Vl
aHWUR0+mJyL+90QYfKtquxd9QJlFAACL3vHRzZPwY+SyzDyJilkA85pGxk7iqCHv
FU3Lm5qNabMfVxFQpRBFfVKeGj6Q42adiD0C87sM8SQs8OXNjqyy8OPco35EiSJ/
NnUaTrujGd+pqxdzlZcOO0pvcP5AUARbU4l3vcOl8CX3jycboi0wOwOl5+K7Yh22
gtYqPB0I8TFBOFr0Uzz3w2oay7szI8FKi3erZYOPN/JwblIImD7PD/FDnvajlyXl
RjQglIHutzZze06fEyVxg90Y6S8d1/D9C9t70aHOuElb2tGDktPvD7VIA5KBYRJV
KiWhIaND4DS38KfnnmDPpN6on6a4L4xuM57HlMrAFMMS/hXQE5hLLJCJeLFnle/A
iXiS7dNiZP/M2birw0QKiq8JbMvgC/0SCPXvFiTJQzaJVtS/j4gpBBqQLPuvA9cw
/d0Tu7NaCK9CB1DYvJuzdauyhpj4T13VYg4FT4AqoHJHzb/4WjBrqOZVM8JegIhP
eiTHSjS+yY3tWaVydtgCEB9N7teIPmx7UBIsamajD7IvHKN7Z15U2VPfqNIqyx6n
kl+xXXyzfQJk5vsjxkAQB0gtAim2nuTC/xYWItNCkTJDEtoQd7b+cM8M4kckWb8G
JXirexdjkfJqq9cMuHwqD0nTaYsi1aO73Ta0eGpzRVsNVeV/cM/yoFVlX1S7kJoo
swjuyoBH30OtFUPduhiDipdIxgBqc6fDV+I35a/emSq6YXFQ1CeorjjaetuW9/nS
/w9tCVJvAG1SYgvP1QCAKjN/ryFNAKwgs4YUOcQp42ZC4HGil0/DaQgYcsz1saa2
aoMO78VoSD7OTFWYIbxfRhODQ7AsdHFP/loKbMrRF13AN7IMwfZB0PUd+resYC59
QYp0PmlzUmQRMRx3jMdz6U9Bhmj0WXlnUj7bTFV7EhDssAgV4l1SV9uVC/lU0N/R
tE6fjotDl+wr80qOliYLjTxe6QeeQIocYWe5ezHZNFFKg9hEuifa82L4vR5SAXpY
CZ38mfcf84Q2tI7qEUBWGIpvzGrq2UxSs/sqCVEFfDKgxzlguzSijpmU8VSLMgdC
PA2IRygDQG+VT5QJx/GF9891FD5rYEaNZJfRNAWe6ev/eizqyCVwR7qsQiGvTIbM
ZSl9OnfA/WPm07N/byF8r/fd+ERSsLq59CNIPCh+QG3z03dYp79DEEq2BPSkX9An
btavR3FWHQIPsOlBT5mkb/POCztV95w1pOhVmIxBfaUsiT2QINvfh12U+yYeHfOi
NwZa9AfFfLkziKNfa4WC+sbBTO6iPSv/wIh+D38AB2eC
-----END ENCRYPTED PRIVATE KEY-----)";
const std::string publicKey = R"(-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAr9qg3gEWzZZsACyrkNVl
w3epUPwbJy1mQwy0QgX0zUVT8G0qtbZi1blkWizXcIDE81IQNCDi3r1GwIvqR2bj
ZRlWe+MHboQ5SnWiOfzjiR3Iy7KhSTF/GID1dDBehg4RWI5AZSYM2iwFZgf9HSZl
/UmJgZRhF39EFXqZymqIfuGNGf2ZVOAdtt3/FkUR4eH11Xi/D3BcYYGdQr7SDAXh
+CQM+ew0Jyrrs7rMhqgKm1t3nnetsxgCmwm4X4lLb2mFB6B8sVjBj8Iyhon5Snhs
IazXfstamx5FHZDFwqafI2cRiizyMkSOPFanEKn54WmHmsPsjQ9qAmgb4CIaDtSC
jwIDAQAB
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



