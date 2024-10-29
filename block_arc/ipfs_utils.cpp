#include <cpr/api.h>
#include <cpr/body.h>
#include <cpr/cprtypes.h>
#include <cpr/multipart.h>
#include <cpr/resolve.h>
#include <cpr/response.h>
#include "nlohmann/json_fwd.hpp"
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>
#include "ipfs_utils.hpp"

// Upload data to IPFS and return the IPFS hash
std::string ipfs_upload(const std::string &data) {
  // post request -> http api
  cpr::Response r =
      cpr::Post(cpr::Url{"http://localhost:5001/api/v0/add"},
                cpr::Multipart{{"file", data}},
                cpr::Header{{"Content-Type", "multipart/form-data"}});
  if (r.status_code == 200) {
    // parse ipfs hash
    nlohmann::json response = nlohmann::json::parse(r.text);
    std::string ipfs_hash = response["Hash"];
    std::cout << "Data Uploaded to IPFS; Hash: " << ipfs_hash << std::endl;
    return ipfs_hash;
  } else {
    std::cerr << "Data Upload to IPFS Failed " << r.status_code << std::endl;
    return "";
  }
}
