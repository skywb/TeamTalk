cmake_minimum_required(VERSION 3.10)

#aux_source_directory(. DIR_LIB_SRCS)




#add_library(IM ${DIR_LIB_SRCS})

add_library(IM SHARED IMProtocol.h IMProtocol.cpp User.h User.cpp )


SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

