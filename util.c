#include "util.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

uint64_t simpleHash64(const char* key)
{
	LOG_FUNCTION_ENTERING();
	assert(key != NULL && strlen(key) > 0);

	uint64_t hash = 1125899906842597;
	int keyLength = strlen(key);

	for(int i = 0; i < keyLength; i++)
		hash = hash * 31 + key[i];

	return hash;
}
