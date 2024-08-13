# Ozone Blockchain
![v1.0.0](https://img.shields.io/badge/version-v1.0.0-blue)


Ozone is a entirely self-developed blockchain compatiable with IPFS to ensure continued decentralization.


## Breakdown

#### BLOCK_ARC:
- block.cpp - Defines block contents, manages hash generation, defines print parameters.
- blockchain.cpp - Initialized genesis block, manages and validates chain.
- hash_utils.cpp - Manages hash/key/signiture generagtion and calculation. 
- ipfs_utils.cpp - Uploads data to ipfs from a given node.
- proof_of_work.cpp - Outlines mining system, hash difficulty, and nonce creation,
- transaction.cpp - Defines transaction structure.

#### NETWORKING:
 - ipfs_actor.scala - Grabs dats from ipfs http link with specific hash (hard-encoded as of now).
 - ipfs_dispatch.scala - Transmits transactions to all nodes on the network.
 - node_actor.scala - Defines node paths and how data is read at nodes. 

 *see more in: OzoneDocs.md*

## Instalation

*No install guide in version 1.0.0*

## Contributions

*coming soon*



 



