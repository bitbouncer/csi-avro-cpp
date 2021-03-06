#include <iostream>
#include <sstream>
#include <openssl/md5.h>
#include "utils.h"
#include "encoding.h"

std::string to_string(const avro::OutputStream& os)
{
    std::string res;
    size_t sz = os.byteCount();
    res.reserve(sz);
    res.resize(sz);
    auto x = avro::memoryInputStream(os);
    avro::StreamReader reader(*x.get());
    //size_t actual = csi::readBytes(&reader, (uint8_t*)&res[0], sz);
	reader.readBytes((uint8_t*)&res[0], sz);
    //assert(actual == sz);
    return res;
}

std::string normalize(const avro::ValidSchema& vs)
{
    std::stringstream ss;
    vs.toJson(ss);
    std::string s = ss.str();
    
    // TBD we should strip type : string to string 

    // strip whitespace
    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());  // c version does not use locale... 
    return s;
}

boost::uuids::uuid generate_hash(const avro::ValidSchema& vs)
{
    std::string s = normalize(vs);
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, s.data(), s.size());
    boost::uuids::uuid uuid;
    MD5_Final(uuid.data, &ctx);
    return uuid;
}

