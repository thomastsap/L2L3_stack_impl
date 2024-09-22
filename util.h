#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
//#define NDEBUG
#include <assert.h>

typedef enum returnValue
{
	SUCCESS = 0, 
	GENERAL_ERROR,

} ret_t;

#ifdef NDEBUG
#define LOG_FUNCTION_ENTERING()
#define DEBUG_LOG(...)
#else
#define LOG_FUNCTION_ENTERING() \
	printf("Entering %s()\n", __FUNCTION__)
#define DEBUG_LOG(...) \
	printf(__VA_ARGS__);
#endif

typedef uint8_t bool;
#define TRUE 1
#define FALSE 0

uint64_t simpleHash64(const char* key);

#endif