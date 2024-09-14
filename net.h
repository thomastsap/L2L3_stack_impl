#ifndef NET_H
#define NET_H

#include "util.h"
#include <stdint.h>

#define NUMBER_OF_BYTES_IN_IPV4 4
#define NUMBER_OF_BYTES_IN_MAC_ADDRESS 6
#define IPV4_ADDRESS_STRING_LENGTH 16 // ex. strlen("255.255.255.255") + 1<terminal char> = 16
#define MAC_ADDRESS_STRING_LENGTH 18 // ex. strlen("00:1b:63:84:45:e6") + 1<terminal char> = 18

typedef uint32_t ipv4AddressUint32_t;

typedef struct ipv4AddressUint8Arr
{
	uint8_t byte[NUMBER_OF_BYTES_IN_IPV4]; // endianess does not matter but we assume the following logic: ex. byte[3] = 192 / byte[2] = 168 / byte[1] = 1 / byte[0] = 1 then ipv4 = 192.168.1.1
} ipv4AddressUint8Arr_t;

// We represent ipv4 as an uint32_t value or as an array of 4 bytes
typedef union ipv4
{
	ipv4AddressUint32_t uint32Rep;
	ipv4AddressUint8Arr_t uint8ArrRep;
} ipv4_t;

typedef struct ipV4AddressStr
{
	char ipV4AddrStr[IPV4_ADDRESS_STRING_LENGTH];
} ipV4Str_t;

typedef struct macAddr
{
	uint8_t byte[NUMBER_OF_BYTES_IN_MAC_ADDRESS];
} macAddr_t;

typedef struct macAddrStr
{
	char macAddrStr[MAC_ADDRESS_STRING_LENGTH];
} macAddressStr_t;

typedef uint8_t netmask_t;

typedef struct nodeNetworkProperties
{
	bool isLoopbackConfigured;
	ipv4_t loopbackAddr;
} nodeNetworkProp_t;

typedef struct interfaceNetworkProperties
{
	macAddr_t macAddr;
	
	bool isIpConfigured;
	ipv4_t ipAddr;
	netmask_t mask;

} interNetworkProp_t;

#endif
