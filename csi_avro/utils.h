#include <memory>
#include <cstring>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/array.hpp>
#include <avro/Stream.hh>
#include <avro/ValidSchema.hh>

#pragma once

inline boost::array<uint8_t, 16> to_array(const boost::uuids::uuid& uuid)
{
    boost::array<uint8_t, 16> a;
    memcpy(a.c_array(), uuid.data, 16);
    return a;
}

inline boost::uuids::uuid to_uuid(const boost::array<uint8_t, 16>& a)
{
    boost::uuids::uuid uuid;
    memcpy(uuid.data, a.data(), 16);
    return uuid;
}

inline std::string to_string(const boost::array<uint8_t, 16>& a)
{
    boost::uuids::uuid uuid;
    memcpy(uuid.data, a.data(), 16);
    return to_string(uuid);
}

//inefficient but useful for debugging and error handling -- remove???
/*
inline std::string to_string(std::auto_ptr<avro::InputStream> pstream)
{
    std::string s;
    const uint8_t* buf;
    size_t len;
    while (pstream->next(&buf, &len))
        s.append((const char*)buf, len);
    return s;
}
*/

std::string        to_string(const avro::OutputStream& os);
std::string        normalize(const avro::ValidSchema&);
boost::uuids::uuid generate_hash(const avro::ValidSchema&);


