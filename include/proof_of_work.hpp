#ifndef PROOF_OF_WORK_HPP
#define PROOF_OF_WORK_HPP

#include <string>
#include "block.hpp"

class ProofOfWork {
public:
    static void mineBlock(Block& block, int difficulty);
};

#endif // PROOF_OF_WORK_HPP
