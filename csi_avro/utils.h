#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/array.hpp>
#include <cstring>

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
