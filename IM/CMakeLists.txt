cmake_minimum_required(VERSION 3.10)

#aux_source_directory(. DIR_LIB_SRCS)




#add_library(IM ${DIR_LIB_SRCS})
set(library_output_path bin)

add_library(IM SHARED IMProtocol.h User.h IMProtocol.cpp User.cpp)


SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

