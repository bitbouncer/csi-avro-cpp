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
#include <boost/uuid/uuid_io.hpp>
#include <csi_avro/utils.h>

template<class OutIter>
OutIter escape_string(std::string const& s, OutIter out) {
    //*out++ = '"';
    for (std::string::const_iterator i = s.begin(), end = s.end(); i != end; ++i) {
        unsigned char c = *i;
        if (' ' <= c && c <= '~' && c != '\\' && c != '"') {
            *out++ = c;
        }
        else {
            *out++ = '\\';
            switch (c) {
            case '"':  *out++ = '"';  break;
            case '\\': *out++ = '\\'; break;
            case '\t': *out++ = 't';  break;
            case '\r': *out++ = 'r';  break;
            case '\n': *out++ = 'n';  break;
            default:
                char const* const hexdig = "0123456789ABCDEF";
                *out++ = 'x';
                *out++ = hexdig[c >> 4];
                *out++ = hexdig[c & 0xF];
            }
        }
    }
    //*out++ = '"';
    return out;
}

int main(int argc, char** argv)
{
    std::string infine;
    std::string outfile;

    if (argc > 1)
        infine = argv[1];

    if (argc > 2)
        outfile = argv[2];

    avro::ValidSchema schema;

    try
    {
        if (!infine.empty())
        {
            std::ifstream in(infine.c_str());
            avro::compileJsonSchema(in, schema);
        }
        else
        {
            avro::compileJsonSchema(std::cin, schema);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Failed to parse or compile schema: " << e.what() << std::endl;
        return 1;
    }

    try{
        if (!outfile.empty())
        {
            
            std::string str  = normalize(schema);
            std::string escaped_string;
            escape_string(str, std::back_inserter(escaped_string));
            std::cerr << escaped_string << std::endl;
            std::ofstream out(outfile);
            out << escaped_string;
        }
        else
        {
            schema.toJson(std::cout);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Failed to write output file: " << outfile << e.what() << std::endl;
        return 1;
    }
    return 0;
}
