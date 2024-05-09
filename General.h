#ifndef __GENERAL__
#define __GENERAL__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "time.h"

#define EXIT -1
#define MAX_LEN 255

#define HANDLE_ERRORS(arg, body,  returnValue) \
    if (!(arg)) { \
        body; \
        return returnValue; \
    }

#define CHECK_IF_EQUALS(val1, val2, returnValue) \
    if(val1 == val2) \
        return returnValue; 

#define CHECK_IF_NOT_EQUALS(val1, val2, returnValue) \
    if(val1 != val2) \
        return returnValue; 

#define CALL_FUNC_IF_TRUE(val, func) \
    if(val) \
        func; 


char*		getStrExactLength(const char* msg);
char*		myGets(char* buffer, int size);
char*		getDynStr(char* str);
void		generalArrayFunction(void* arr, int size, size_t typeSize, void (*f)(void*));
int			getPositiveNumber(char* str);
int			getNumberInRange(char* str, int start, int end);
void        printHeader(char* str);
void        timeDelay(int number_of_seconds);




#endif

