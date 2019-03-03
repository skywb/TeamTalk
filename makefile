
VPATH=source:header

OBJ=DBUtil.o User.o
CPPFLAGS= -I header -lmysqlcppconn


main : $(OBJ)
	g++ $(OBJ) $(CPPFLAGS) -o main

%.o : %.h %.c
	g++ -c $(CPPFLAGS) %<



.PHONY : test

test: test.o compileObj
	g++ test.o $(OBJ) $(CPPFLAGS) -o test

compileObj : $(OBJ)


.PHONY : clean

clean : 
	rm *.o
