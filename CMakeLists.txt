cmake_minimum_required(VERSION 3.10)

project(zchain)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set OpenSSL root directory
set(OPENSSL_ROOT_DIR /opt/homebrew/Cellar/openssl@3/3.3.1)

# Include directories for OpenSSL
include_directories(${OPENSSL_ROOT_DIR}/include)

# Link directories for OpenSSL
link_directories(${OPENSSL_ROOT_DIR}/lib)

include_directories(include)
# Add the path to nlohmann/json.hpp
include_directories(/opt/homebrew/Cellar/nlohmann-json/3.11.3/include)
include_directories(/opt/homebrew/Cellar/openssl@3/3.3.1/include)
include_directories(include)
include_directories(/opt/homebrew/lib)
include_directories(/opt/homebrew/Cellar/openssl@3/3.3.1/lib)
include_directories(/opt/homebrew/Cellar/openssl@3/3.3.1/lib/pkgconfig)
include_directories(/opt/homebrew/Cellar/cpr)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find CPR package installed via Homebrew
find_package(cpr REQUIRED)
include_directories(${CPR_INCLUDE_DIRS})

add_executable(zchain
    block_arc/main.cpp
    block_arc/block.cpp
    block_arc/blockchain.cpp
    block_arc/hash_utils.cpp
    block_arc/proof_of_work.cpp
    block_arc/transaction.cpp
    block_arc/ipfs_utils.cpp# Add this line if not present
)

# Link the OpenSSL libraries explicitly
target_link_libraries(zchain
    ${OPENSSL_ROOT_DIR}/lib/libssl.dylib
    ${OPENSSL_ROOT_DIR}/lib/libcrypto.dylib
    cpr::cpr
)

