#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

typedef enum returnValue
{
	SUCCESS = 0, 
	GENERAL_ERROR,

} ret_t;

#define LOG_FUNCTION_ENTERING() \
	printf("Entering %s()\n", __FUNCTION__)

typedef uint8_t bool;
#define TRUE 1
#define FALSE 0

#endif