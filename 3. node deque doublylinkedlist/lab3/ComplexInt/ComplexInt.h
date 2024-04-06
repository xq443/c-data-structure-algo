#ifndef COMPLEX_INT_H 

#define COMPLEX_INT_H 

typedef struct ComplexInt{
        int* data;
}ComplexInt;

ComplexInt* createComplexInt(int val){
	// Allocate memory for the ComplexInt struct
        ComplexInt* complexInt = (ComplexInt*)malloc(sizeof(ComplexInt));
        if(complexInt == NULL){
                printf("Memory allocation failed for ComplexInt.\n");
                exit(1);
        }
	// Allocate memory for the ComplexInt data
        complexInt->data = (int*)malloc(sizeof(int));
        if(complexInt->data == NULL){
                printf("Memory allocation failed for ComplexInt data.\n");
                exit(1);
        }
	//Assign val to the memory location of the pointer
        *(complexInt->data) = val;

        return complexInt;
}

#endif
