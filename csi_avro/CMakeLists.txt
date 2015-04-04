SET(LIB_SRCS
    encoding.h
    encoding.cpp
    utils.h
    md5.h
    md5.cpp
	)
add_library (csi-avro STATIC ${LIB_SRCS})