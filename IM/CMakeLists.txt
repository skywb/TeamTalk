cmake_minimum_required(VERSION 3.10)

#aux_source_directory(. DIR_LIB_SRCS)




#add_library(IM ${DIR_LIB_SRCS})
add_library(IM IMProtocol.h User.h IMProtocol.cpp User.cpp)


