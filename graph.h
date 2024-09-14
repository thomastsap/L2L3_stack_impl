#ifndef GRAPH_H
#define GRAPH_H

#include "net.h"

typedef struct interface interface_t;
typedef struct node node_t;

typedef struct link
{
	unsigned int id;
	interface_t* interface1;
	interface_t* interface2;
	unsigned int cost; // maybe of no use for now
} link_t;

typedef struct interface
{
	unsigned int id;
	char* name;
	node_t* owningNode;
	link_t* owningLink;
	interNetworkProp_t* interNetworkProp;
	interface_t* next;
} interface_t;

typedef struct node
{
	unsigned int id;
	char* name;
	interface_t* interface;
	nodeNetworkProp_t* nodeNetworkProp;
	node_t* next;
} node_t;

typedef struct graph
{
	char* name;
	node_t* node;
} graph_t;

node_t* getInterfaceOwningNode(interface_t* interface);
graph_t* createNewGraph(char* topologyName);
void printGraph(graph_t* graph);
node_t* createGraphNode(graph_t* graph, char* nodeName);
interface_t* createNodeInterface(node_t* node, char* interfaceName);
link_t* createLinkBetweenInterfaces(interface_t* interface1, interface_t* interface2, unsigned int linkCost);
link_t* insertLinkBetweenNodes(node_t* fromNode, char* fromInterfaceName, node_t* toNode, char* toInterfaceName, unsigned int linkCost);
interface_t* searchNodeForInterfaceByName(node_t* node, char* interfaceName);
node_t* searchGraphForNodeByName(graph_t* graph, char* nodeName);

#endif