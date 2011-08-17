#include <AoTK/aotk.h>

#include <iostream>

int my_assert_true(bool b,const char * msg);
int my_assert_false(bool b,const char * msg);


int my_assert_true(bool b,const char * msg){
	if(!b){
		std::cerr << msg << std::endl;
	}
	return b ? 0 : 1;
}

int my_assert_false(bool b,const char * msg){
	return my_assert_true(!b,msg);
}
