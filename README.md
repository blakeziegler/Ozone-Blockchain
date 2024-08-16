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

Clone the Repository:
```
git clone https://github.com/blakeziegler/Ozone-Blockchain.git
```

#### Ensure Dependencies are Installed:

- C++ version 17+
    - CMake version 3.10+
    - Conan
    - OpenSSL
- Scala version 3
    - SBT
    - Akka
- IPFS

#### Getting Started:

***Testing the Blockchain***

In the /Ozone-Blockchain Directory:

Create a Cmake file by running the command:
```
touch CMakeLists.txt
touch conanfile.txt
```


Make a Private and Public Blockchain Key:
```
openssl genpkey -algorithm RSA -out private_key.pem -aes256
openssl rsa -in private_key.pem -pubout -out public_key.pem
```
Copy and Paste your Keys into main.cpp in the Space Provided
See your Keys with the following commands:
```
cat private_key.pem
cat public_key.pem
```

***Note: Do NOT add changes to git with your keys in main.cpp***


Make and Open a build Directory:
```
mkdir build
```

Install Dependencies Using Conan *(See conanfile.txt template before installing)*
```
conan install . --output-folder=build --build=missing -s build_type=Release
```

Build Project with CMake *(See CMakeLists.txt template before building):*
```
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```


Run the Program:
```
./ozone
```

#### CMakeLists.txt Template
```
cmake_minimum_required(VERSION 3.10)
project(ozone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

add_executable(ozone
    block_arc/main.cpp
    block_arc/block.cpp
    block_arc/hash_utils.cpp
    block_arc/proof_of_work.cpp
    block_arc/transaction.cpp
    block_arc/ipfs_utils.cpp
    block_arc/blockchain.cpp
)
find_package(OpenSSL REQUIRED)
find_package(CURL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(CPR REQUIRED)

target_link_libraries(ozone
    OpenSSL::SSL
    OpenSSL::Crypto
    CPR::cpr
    CURL::libcurl
    ZLIB::ZLIB
)
```

#### conanfile.txt Template
```
[requires]
cpr/1.10.5
openssl/3.1.0
zlib/1.2.11
libcurl/7.68.0

[generators]
CMakeToolchain
CMakeDeps
```

#### IPFS Testing:
*coming soon*

## Contributions

*coming soon*



 



