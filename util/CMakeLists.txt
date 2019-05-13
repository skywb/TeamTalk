
#aux_source_directory(. DIR_LIB_SRCS)


#add_library(Util ${DIR_LIB_SRCS})
add_library(Util SHARED Log.cpp Log.h sockUtil.h sockUtil.cpp UtilPdu.h UtilPdu.cpp testUtil.h DBUtil.h DBUtil.cpp)


SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
