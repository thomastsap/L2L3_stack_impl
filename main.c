#include <stdio.h>
#undef NDEBUG // when defined, remove assertions from code
#include <assert.h>
#include "graph.h"

int main(void)
{
	graph_t* newGraph = createNewGraph("NewGraph");
	node_t* node1 = createGraphNode(newGraph, "thomas1");
	node_t* node2 = createGraphNode(newGraph, "thomas2");
	node_t* node3 = createGraphNode(newGraph, "thomas3");
	node_t* node4 = createGraphNode(newGraph, "thomas4");

	insertLinkBetweenNodes(node1, "if1_1", node2, "if2_1", 1);
	insertLinkBetweenNodes(node1, "if1_2", node3, "if3_1", 1);
	insertLinkBetweenNodes(node1, "if1_3", node4, "if4_1", 1);

	printGraph(newGraph);

	interface_t* foundInterface1 = searchNodeForInterfaceByName(node1, "if1_1");
	assert(foundInterface1 != NULL);

	interface_t* foundInterface2 = searchNodeForInterfaceByName(node2, "if2_1");
	assert(foundInterface2 != NULL);

	interface_t* notFoundInterface = searchNodeForInterfaceByName(node1, "if2_1");
	assert(notFoundInterface == NULL);

	node_t* foundNode1 = searchGraphForNodeByName(newGraph, "thomas1");
	assert(foundNode1 != NULL);

	node_t* foundNode2 = searchGraphForNodeByName(newGraph, "thomas2");
	assert(foundNode2 != NULL);

	node_t* notFoundNode = searchGraphForNodeByName(newGraph, "thomas5");
	assert(notFoundNode == NULL);

	macAddressStr_t mac;

	ipv4_t ipv4;

	ipv4.uint8ArrRep.byte[0] = 16;

	printf("%d\n", ipv4.uint8ArrRep.byte[0]);

	return 0;
}