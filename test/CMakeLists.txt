cmake_minimum_required(VERSION 2.8.2)


#include_directories("../")


#add_executable(test testProtocol.cpp)
add_executable(testReactor testReactor.cpp Mytask.cpp)
add_executable(ProtocolClient ProtocolClient.cpp)



target_link_libraries(testReactor IM Util Reactor pthread)
target_link_libraries(ProtocolClient IM Util Reactor pthread)




