#include <avro/Specific.hh>
#include <avro/Encoder.hh>
#include <avro/Decoder.hh>
#include "utils.h"

#pragma once

namespace csi
{
    template<class T>
    void avro_json_encode(const T& src, avro::OutputStream& dst)
    {
        avro::EncoderPtr e = avro::jsonEncoder(T::valid_schema());
        e->init(dst);
        avro::encode(*e, src);
        // push back unused characters to the output stream again... really strange...                         
        // otherwise content_length will be a multiple of 4096
        e->flush();
    }

    template<class T>
    T& avro_json_decode(const avro::OutputStream& src, T& dst)
    {
        auto mis = avro::memoryInputStream(src);
        avro::DecoderPtr e = avro::jsonDecoder(T::valid_schema());
        e->init(*mis);
        avro::decode(*e, dst);
        return dst;
    }

    // missing funktion in avro::StreamReader* 
    size_t readBytes(avro::StreamReader* stream, uint8_t* b, size_t n);

    template<class T>
    void avro_binary_encode(const T& src, avro::OutputStream& dst)
    {
        avro::EncoderPtr e = avro::binaryEncoder();
        e->init(dst);
        avro::encode(*e, src);
        // push back unused characters to the output stream again... really strange...                         
        // otherwise content_length will be a multiple of 4096
        e->flush();
    }

    template<class T>
    T& avro_binary_decode(const avro::OutputStream& src, T& dst)
    {
        auto mis = avro::memoryInputStream(src);
        avro::DecoderPtr e = avro::binaryDecoder();
        e->init(*mis);
        avro::decode(*e, dst);
        return dst;
    }

    template<class T>
    size_t avro_binary_encode(const T& src, char* buffer, size_t capacity)
    {
        //write the data
        auto os = avro::memoryOutputStream();
        avro::EncoderPtr e = avro::binaryEncoder();
        e->init(*os.get());
        avro::encode(*e, src);
        // push back unused characters to the output stream again... really strange...                         
        // otherwise content_length will be a multiple of 4096
        e->flush();

        //get the data from the internals of avro stream
        auto x = avro::memoryInputStream(*os.get());
        avro::StreamReader reader(*x.get());
        size_t content_length1 = os->byteCount();
        assert(content_length1 <= capacity);
        size_t content_length2 = csi::readBytes(&reader, (uint8_t*)buffer, capacity);
        assert(content_length1 == content_length2);
        return content_length1;
    }

    // encodes fingerprint first in 16 bytes
    template<class T>
    void avro_binary_encode_with_fingerprint(const T& src, avro::OutputStream& dst)
    {
        avro::EncoderPtr e = avro::binaryEncoder();
        e->init(dst);
        avro::encode(*e, to_array(src.schema_hash())); // you need to generate your classes with csi_avrogencpp - it adds this method
        avro::encode(*e, src);
        // push back unused characters to the output stream again... really strange... 			
        // otherwise content_length will be a multiple of 4096
        e->flush();
    }

    template<class T>
    bool avro_binary_decode_with_fingerprint(avro::InputStream& is, T& dst)
    {
        boost::array<uint8_t, 16> schema_id;
        avro::DecoderPtr e = avro::binaryDecoder();
        e->init(is);
        avro::decode(*e, schema_id);
        if (dst.schema_hash() != to_uuid(schema_id)) // you need to generate your classes with csi_avrogencpp - it adds this method
        {
            return false;
        }

        try
        {
            avro::decode(*e, dst);
        }
        catch (...)
        {
            return false;
        }
        return true;
    }

    template<class T>
    bool avro_binary_decode_with_fingerprint(const avro::OutputStream& src, T& dst)
    {
        auto mis = avro::memoryInputStream(src);
        return avro_binary_decode_with_schema(*mis);
    }

    template<class T>
    T& avro_binary_decode(const char* buffer, size_t size, T& dst)
    {
        auto src = avro::memoryInputStream((const uint8_t*)buffer, size);
        avro::DecoderPtr e = avro::binaryDecoder();
        e->init(*src);
        avro::decode(*e, dst);
        return dst;
    }
}; // csi

