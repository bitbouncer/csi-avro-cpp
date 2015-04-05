#include <iostream>
#include <sstream>
#include "utils.h"
#include "md5.h"

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
    MD5Context ctx;
    MD5Update(&ctx, (const uint8_t*)s.data(), s.size());
    return MD5Final(&ctx);
}