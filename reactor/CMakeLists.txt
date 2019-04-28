
#aux_source_directory(. DIR_LIB_SRCS)



#add_library(Reactor ${DIR_LIB_SRCS})
add_library(Reactor Addresser.cpp Addresser.h Connecter.cpp Connecter.h IMReactor.cpp IMReactor.h )


