SET(LIB_SRCS
    md5.h
    md5.cpp
	)
add_library (csi_avro STATIC ${LIB_SRCS})