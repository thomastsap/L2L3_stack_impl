#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "net.h"
#include "util.h"
#include "graph.h"


ret_t setLoopbackAddrOfNode(node_t* node, ipv4_t ipv4)
{
	LOG_FUNCTION_ENTERING();

	assert(node != NULL);

	node->nodeNetworkProp->loopbackAddr = ipv4;
	node->nodeNetworkProp->isLoopbackConfigured = TRUE;

	return SUCCESS;
}

ret_t setIpAddrOfNodeInterface(node_t* node, char* interfaceName, ipv4_t ipv4, netmask_t mask)
{
	LOG_FUNCTION_ENTERING();

	assert(node != NULL && interfaceName != NULL && strlen(interfaceName) > 0);
	interface_t* interface = searchNodeForInterfaceByName(node, interfaceName);
	
	assert(interface != NULL);
	interface->interNetworkProp->ipAddr = ipv4;
	interface->interNetworkProp->isIpConfigured = TRUE;
	interface->interNetworkProp->mask = mask;

	return SUCCESS;
}