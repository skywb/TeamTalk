cmake_minimum_required(VERSION 3.10)


project(TeamTalk)

include_directories(".")


aux_source_directory(. DIR_SRC)

add_subdirectory(IM)
add_subdirectory(reactor)
add_subdirectory(util)

#add_executable(main ${DIR_SRC})
add_executable(main ${DIR_SRC})

target_link_libraries(main IM Util Reactor pthread)

