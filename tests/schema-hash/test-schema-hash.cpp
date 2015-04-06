#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <fstream>
#include <avro/Compiler.hh>
#include <avro/Schema.hh>
#include <avro/ValidSchema.hh>
#include <sstream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <csi_avro/utils.h>

//#include <openssl/md5.h>


boost::uuids::uuid generate_hash(const char* schema)
{
    const avro::ValidSchema validSchema(avro::compileJsonSchemaFromString(schema));
    boost::uuids::uuid uuid = generate_hash(validSchema);
    return uuid;
}

struct testcase
{
    const char* hash;
    const char* schema;

};

std::vector<testcase> tests = 
{ 
    { "095d71cf-1255-6b9d-5e33-0ad575b3df5d", "\"string\"" } 
};

int main(int argc, char** argv)
{
    for (std::vector<testcase>::const_iterator i = tests.begin(); i != tests.end(); ++i)
    {
        std::string hash          = to_string(generate_hash(i->schema));
        if (hash.compare(i->hash) == 0)
        {
            std::cout << "OK " << hash << std::endl;
        }
        else
        {
            std::cout << "FAILED got:" << hash << ", expected:" << i->hash << std::endl;
        }
    }
}


