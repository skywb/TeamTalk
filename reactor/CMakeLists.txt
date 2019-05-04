
#aux_source_directory(. DIR_LIB_SRCS)



#add_library(Reactor ${DIR_LIB_SRCS})
add_library(Reactor SHARED Addresser.cpp Addresser.h Connecter.cpp Connecter.h IMReactor.cpp IMReactor.h task.h task.cpp)


SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
