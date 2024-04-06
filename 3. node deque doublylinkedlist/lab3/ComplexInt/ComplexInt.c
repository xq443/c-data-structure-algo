#include <stdio.h>
#include <stdlib.h>
#include "ComplexInt.h"


int main(){
	int exampleInt = 2;

	int* exampleIntPtr =  &exampleInt;

	printf("Value of the integer: %d\n", exampleInt);

	printf("Value pointed to by the pointer: %d\n", *exampleIntPtr);

	//test the complexInt function
	ComplexInt* testComplexInt = createComplexInt(100);
	printf("Value pointed to by the pointer: %d\n", *(testComplexInt->data));

	free(testComplexInt->data);
	free(testComplexInt);

	return 0;

}

