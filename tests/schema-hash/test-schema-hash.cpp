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
    { "ccda95e1-5cdf-5438-be1b-c8cab417fede", "\"string\"" } 
};

int main(int argc, char** argv)
{
    for (std::vector<testcase>::const_iterator i = tests.begin(); i != tests.end(); ++i)
    {
        std::string was = to_string(generate_hash(i->schema));
        if (was.compare(i->hash) == 0)
        {
            std::cout << "OK " << was << std::endl;
        }
        else
        {
            std::cout << "FAILED was:" << was << ", expected:" << i->schema << std::endl;
        }
    }
    std::cerr << "hash: " << to_string(generate_hash("\"string\"")) << std::endl;
}


