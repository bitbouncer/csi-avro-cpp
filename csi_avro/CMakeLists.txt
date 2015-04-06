SET(LIB_SRCS
    encoding.h
    encoding.cpp
    utils.h
    utils.cpp
	)
add_library (csi-avro STATIC ${LIB_SRCS})