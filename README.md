# csi-avro-cpp

Bit's and pieces that is "missing" from official avrocpp release.

csi_avrogencpp
adds the following new static methods to generated classes
  - static inline const boost::uuids::uuid schema_hash() 
  - static inline const char* schema_as_string()
  - static const avro::ValidSchema valid_schema()
  
avro_normalize_schema
 - outputs normalized schema to cout
 
 

Building
see
https://github.com/bitbouncer/csi-build-scripts
