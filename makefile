
VPATH=source:header

OBJ=DBUtil.o User.o
CPPFLAGS= -I header


main : $(OBJ)
	g++ $(OBJ) $(CPPFLAGS) -lmysqlcppconn -o main

%.o : %.h %.c
	g++ $(CPPFLAGS) -c builder/%<



.PHONY : test

test: test.o compileObj
	g++ test.o $(OBJ) $(CPPFLAGS) -o test

compileObj : $(OBJ)


.PHONY : clean

clean : 
	rm *.o










SRC_DIR := ./source
BUILD_DIR := ./build
OBJ_DIR := $(BUILD_DIR)/obj
HEADER_DIR := ./header

CPPFLAGS := -Wall -I $(HEADER_DIR)



