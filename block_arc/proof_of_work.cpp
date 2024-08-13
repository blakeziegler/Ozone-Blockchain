#include "proof_of_work.hpp"
#include "hash_utils.hpp"

// mining params
void ProofOfWork::mineBlock(Block &block,
                            int difficulty) { // difficulty = # of leading 0's
  std::string target(difficulty, '0');        // init difficulty @ 0
  do {
    block.nonce =
        std::to_string(std::stoll(block.nonce) + 1); // nonce incrimentation
    // generate hash for new block
    block.hash = Block::createHash(block.getIdx(), block.getPrevHash(),
                                   block.getContents(), block.getNonce());
  } while (block.hash.substr(0, difficulty) !=
           target); // loop until hash is cracked
}
