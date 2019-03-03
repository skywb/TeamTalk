test : DBUtil.h DBUtil.o test.o
	g++ DBUtil.o test.o -lmysqlcppconn -o main

DBUtil.o : DBUtil.h User.o DBUtil.cpp
	g++ -c DBUtil.cpp -o DBUtil.o

test.o : DBUtil.h test.cpp
	g++ -c test.cpp -o test.o

User.o : User.h
	g++ -c User.cpp -o User.o


