#include <stdio.h>
#include <string.h>
#include "net.h"
#include "util.h"
#include "graph.h"
#include <stdlib.h>
#include <inttypes.h>

#define BITS_IN_HEX 4

void convertIpv4ToString(ipv4_t ipv4, ipV4Str_t* ipv4Str)
{
	LOG_FUNCTION_ENTERING();
	assert(ipv4Str != NULL);

	for(int i = 0; i < NUMBER_OF_BYTES_IN_IPV4; i++)
	{
		unsigned int ipv4Triplet = (unsigned int)ipv4.uint8ArrRep.byte[i];

		if(ipv4Triplet > 100)
		{
			sprintf(ipv4Str->ch + strlen(ipv4Str->ch), "%u", ipv4Triplet / 100);
			ipv4Triplet = ipv4Triplet % 100;
			sprintf(ipv4Str->ch + strlen(ipv4Str->ch), "%u", ipv4Triplet / 10);
			sprintf(ipv4Str->ch + strlen(ipv4Str->ch), "%u", ipv4Triplet % 10);
		}
		else if(ipv4Triplet > 10)
		{
			sprintf(ipv4Str->ch + strlen(ipv4Str->ch), "%u", ipv4Triplet / 10);
			sprintf(ipv4Str->ch + strlen(ipv4Str->ch), "%u", ipv4Triplet % 10);
		}
		else
		{
			sprintf(ipv4Str->ch + strlen(ipv4Str->ch), "%u", ipv4Triplet);
		}

		if(i < NUMBER_OF_BYTES_IN_IPV4 - 1)
			sprintf(ipv4Str->ch + strlen(ipv4Str->ch), ".");
	}

	return;
}

void convertStringToIpv4(char* ipv4Str, ipv4_t* ipv4)
{
	LOG_FUNCTION_ENTERING();
	assert(ipv4 != NULL && ipv4Str != NULL && strlen(ipv4Str) > 0);
	
	char* ipv4StrTriplet = NULL;
	int i = 0;

	for(i = 0, ipv4StrTriplet = strtok(ipv4Str, "."); ipv4StrTriplet != NULL; i++, ipv4StrTriplet = strtok(NULL, "."))
	{
		ipv4->uint8ArrRep.byte[i] = atoi(ipv4StrTriplet);	
		DEBUG_LOG("%s %d\n", ipv4StrTriplet, ipv4->uint8ArrRep.byte[i]);
	}

	return;
}

void setMacAddrOfInterface(interface_t* interface)
{
	LOG_FUNCTION_ENTERING();
	assert(interface != NULL);

	uint64_t macAddrHash = simpleHash64(interface->name) * 31 + simpleHash64(interface->owningNode->name);

	interface->interNetworkProp = (interNetworkProp_t*)calloc(1, sizeof(interNetworkProp_t));
	assert(interface->interNetworkProp != NULL);

	// From the 64bit hash used to generate the mac address we only use the 48 bits. We ignore the last 16 bits

	interface->interNetworkProp->macAddr.byte[0] = (macAddrHash & 0x0000000000FF0000) >> (4 * BITS_IN_HEX);
	interface->interNetworkProp->macAddr.byte[1] = (macAddrHash & 0x00000000FF000000) >> (6 * BITS_IN_HEX);
	interface->interNetworkProp->macAddr.byte[2] = (macAddrHash & 0x000000FF00000000) >> (8 * BITS_IN_HEX);
	interface->interNetworkProp->macAddr.byte[3] = (macAddrHash & 0x0000FF0000000000) >> (10 * BITS_IN_HEX);
	interface->interNetworkProp->macAddr.byte[4] = (macAddrHash & 0x00FF000000000000) >> (12 * BITS_IN_HEX);
	interface->interNetworkProp->macAddr.byte[5] = (macAddrHash & 0xFF00000000000000) >> (14 * BITS_IN_HEX);

	DEBUG_LOG("%" PRIu64 "\n", macAddrHash);
	DEBUG_LOG("%d\n", interface->interNetworkProp->macAddr.byte[0]);
	DEBUG_LOG("%d\n", interface->interNetworkProp->macAddr.byte[1]);
	DEBUG_LOG("%d\n", interface->interNetworkProp->macAddr.byte[2]);
	DEBUG_LOG("%d\n", interface->interNetworkProp->macAddr.byte[3]);
	DEBUG_LOG("%d\n", interface->interNetworkProp->macAddr.byte[4]);
	DEBUG_LOG("%d\n", interface->interNetworkProp->macAddr.byte[5]);

	return;
}

void convertMacAddrToString(macAddr_t macAddr, macAddressStr_t* macAddrStr)
{
	LOG_FUNCTION_ENTERING();
	assert(macAddrStr != NULL);

	for(int i = 0; i < NUMBER_OF_BYTES_IN_MAC_ADDRESS; i++)
	{
		sprintf(macAddrStr->ch + strlen(macAddrStr->ch), "%02hhX", macAddr.byte[i]);
		if(i < NUMBER_OF_BYTES_IN_MAC_ADDRESS - 1)
			sprintf(macAddrStr->ch + strlen(macAddrStr->ch), ":");
	}

	DEBUG_LOG("%s\n", macAddrStr->ch );

	return;
}

void setLoopbackAddrOfNode(node_t* node, ipv4_t ipv4)
{
	LOG_FUNCTION_ENTERING();
	assert(node != NULL);

	node->nodeNetworkProp = (nodeNetworkProp_t*)calloc(1, sizeof(nodeNetworkProp_t));
	assert(node->nodeNetworkProp != NULL);

	node->nodeNetworkProp->loopbackAddr = ipv4;
	node->nodeNetworkProp->isLoopbackConfigured = TRUE;

	return;
}

void setStrLoopbackAddrOfNode(node_t* node, ipV4Str_t* ipv4Str)
{
	LOG_FUNCTION_ENTERING();
	assert(node != NULL && ipv4Str != NULL && strlen(ipv4Str->ch) > 0);

	node->nodeNetworkProp = (nodeNetworkProp_t*)calloc(1, sizeof(nodeNetworkProp_t));
	assert(node->nodeNetworkProp != NULL);

	ipv4_t ipv4;
	memset(&ipv4, 0, sizeof(ipv4));

	convertStringToIpv4(ipv4Str->ch, &ipv4);
	setLoopbackAddrOfNode(node, ipv4);

	return;
}

void setIpAddrOfNodeInterface(node_t* node, char* interfaceName, ipv4_t ipv4, netmask_t mask)
{
	LOG_FUNCTION_ENTERING();
	assert(node != NULL && interfaceName != NULL && strlen(interfaceName) > 0);
	
	interface_t* interface = searchNodeForInterfaceByName(node, interfaceName);
	assert(interface != NULL);

	interface->interNetworkProp->ipAddr = ipv4;
	interface->interNetworkProp->isIpConfigured = TRUE;
	interface->interNetworkProp->mask = mask;

	return;
}

void setStrIpAddrOfNodeInterface(node_t* node, char* interfaceName, ipV4Str_t* ipv4Str, netmask_t mask)
{
	LOG_FUNCTION_ENTERING();
	assert(node != NULL && interfaceName != NULL && strlen(interfaceName) > 0 && ipv4Str != NULL && strlen(ipv4Str->ch) > 0);
	
	interface_t* interface = searchNodeForInterfaceByName(node, interfaceName);
	assert(interface != NULL);

	ipv4_t ipv4;
	memset(&ipv4, 0, sizeof(ipv4));

	convertStringToIpv4(ipv4Str->ch, &ipv4);
	setIpAddrOfNodeInterface(node, interfaceName, ipv4, mask);

	return;
}