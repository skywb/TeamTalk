cmake_minimum_required(VERSION 3.10)


set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")




project(TeamTalk)

include_directories(".")


aux_source_directory(. DIR_SRC)

add_subdirectory(IM)
add_subdirectory(reactor)
add_subdirectory(util)
add_subdirectory(dao)
add_subdirectory(server)
add_subdirectory(test)


#SET(LIBRARY_OUTPUT_PATH lib)


#add_executable(server server.cpp)
#add_executable(main ${DIR_SRC})

#target_link_libraries(server IM Util Reactor dao mysqlcppconn pthread)


#enable_testing()
#
#add_test(NAME TDao COMMAND testDao)
