# Ozone Blockchain

Ozone is a entirely self-developed blockchain compatiable with IPFS to ensure continued decentralization.


## Directory Structure

- /ozone/
    | block_arc/
        | block.cpp
        | blockchain.cpp
        | hash_utils.cpp
        | ipfs_utils.cpp
        | main.cpp
        | proof_of_work.cpp
        | transaction.cpp
    | include/ 
        | block.hpp
        | blockchain.hpp
        | hash_utils.hpp
        | ipfs_utils.hpp
        | main.hpp
        | proof_of_work.hpp
        | transaction.hpp
    | networking/
        | build.sbt
        | src/
            | main/
                |scala/
                    | Main.scala
                    | chain_network.scala
                    | ipfs_actor.scala
                    | ipfs_dispatch.scala
                    | node_actor.scala
    | CMakeLists.txt
    | CMakeFiles/
    | Makefile
    | README.md 
    | .gitignore

## Breakdown

### BLOCK_ARC:
- block.cpp - Defines block contents, manages hash generation, defines print parameters.
- blockchain.cpp - Initialized genesis block, manages and validates chain.
- hash_utils.cpp - Manages hash/key/signiture generagtion and calculation. 
- ipfs_utils.cpp - Uploads data to ipfs from a given node.
- proof_of_work.cpp - Outlines mining system, hash difficulty, and nonce creation,
- transaction.cpp - Defines transaction structure.

### NETWORKING:
 - ipfs_actor.scala - Grabs dats from ipfs http link with specific hash (hard-encoded as of now).
 - ipfs_dispatch.scala - Transmits transactions to all nodes on the network.
 - node_actor.scala - Defines node paths and how data is read at nodes. 

 *see more in: OzoneDocs.md*

## Instalation

*No install guide in version 1.0.0.BETA*

## Contributions

*coming soon*



 



