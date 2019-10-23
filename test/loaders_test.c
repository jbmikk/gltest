#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "matrix.h"
#include "ctest.h"

void t_setup(){
}

void t_teardown(){
}

void load_obj_test(){
	t_assert(1 == 1);
}

int main(int argc, char** argv){

	t_init();
	t_test(load_obj_test);

	return t_done();
}

