cmake_minimum_required(VERSION 2.8.2)


#include_directories("../")


#add_executable(test testProtocol.cpp)
add_executable(testReactor testReactor.cpp)
#add_executable(ProtocolServer ProtocolServer.cpp Mytask.cpp)
add_executable(ProtocolClient ProtocolClient.cpp)
#add_executable(testDao testUserDao.cpp)
#add_executable(testUserDao_add testUserDao_add.cpp)
#add_executable(testUserDao_select testUserDao_select.cpp)
#add_executable(testUserDao_del testUserDao_del.cpp)
#add_executable(testUserDao_update testUserDao_update.cpp)



target_link_libraries(testReactor Util Reactor IM dao mysqlcppconn pthread)
#target_link_libraries(ProtocolServer IM Util Reactor pthread)
target_link_libraries(ProtocolClient IM Util Reactor dao mysqlcppconn pthread)
#target_link_libraries(testDao dao IM Util Reactor mysqlcppconn gtest gtest_main pthread )
#target_link_libraries(testUserDao_add dao IM Util Reactor mysqlcppconn gtest gtest_main pthread )
#target_link_libraries(testUserDao_select dao IM Util Reactor mysqlcppconn gtest gtest_main pthread )
#target_link_libraries(testUserDao_del dao IM Util Reactor mysqlcppconn gtest gtest_main pthread )
#target_link_libraries(testUserDao_update dao IM Util Reactor mysqlcppconn gtest gtest_main pthread )




