#ifndef TESTUTIL_H_UI1EO8UB
#define TESTUTIL_H_UI1EO8UB

#include <iostream>


void printBity(const char* arg, size_t len)  {
	
	char ch;
	for(int i=0; i<len; ++i) {
		ch = *(arg+i);
		for(int j=0; j < 8; ++j) {
			std::cout << ((ch & (1 << j)) ? 1: 0);
		}
	}
	std::cout <<  std::endl;

}




#endif /* end of include guard: TESTUTIL_H_UI1EO8UB */

