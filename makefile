
VPATH=./source:./header:./build
D_SRC := ./source
D_BUILD := ./build
#D_OBJ := $(D_BUILD)
D_HEADER := ./header
LIB := pthread
CPPFLAGS := -Wall -I $(D_HEADER) -fstack-protector -fstack-protector-all -g 


OBJ := IMReactor.o UtilLog.o sockUtil.o

P_OBJ := $(addprefix $(D_BUILD)/, $(OBJ))


main : $(P_OBJ) main.cpp
	g++ $(CPPFLAGS) -o main $(P_OBJ) $(D_SRC)/main.cpp -l $(LIB)

$(D_BUILD)/IMReactor.o : IMReactor.cpp IMReactor.h
	g++ -c $(CPPFLAGS) -o $(D_BUILD)/IMReactor.o $(D_SRC)/IMReactor.cpp


$(D_BUILD)/UtilLog.o : UtilLog.cpp UtilLog.h
	g++ -c $(CPPFLAGS) -o $(D_BUILD)/UtilLog.o $(D_SRC)/UtilLog.cpp


$(D_BUILD)/sockUtil.o : sockUtil.cpp sockUtil.h
	g++ -c $(CPPFLAGS) -o $(D_BUILD)/sockUtil.o $(D_SRC)/sockUtil.cpp



.PHONY: clean

clean : 
	rm ./build/*.o
