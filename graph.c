#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "util.h"

void setMacAddrOfInterface(interface_t* interface);

node_t* getInterfaceOwningNode(interface_t* interface)
{
	LOG_FUNCTION_ENTERING();
	assert(interface != NULL);
	return interface->owningNode;
}

graph_t* createNewGraph(char* topologyName)
{
	LOG_FUNCTION_ENTERING();
	assert(topologyName != NULL && strlen(topologyName) != 0);

	graph_t* graph = (graph_t*)calloc(1, sizeof(graph_t));
	assert(graph != NULL);

	graph->name = (char*)calloc(1, strlen(topologyName) + 1 /*terminal char*/ );
	assert(graph->name != NULL);

	strncpy(graph->name, topologyName, strlen(topologyName));	
	graph->name[strlen(graph->name)] = '\0';

	return graph;
}

void freeGraph(graph_t* graph)
{
	LOG_FUNCTION_ENTERING();
	assert(graph != NULL);

	if(graph->name)
		free(graph->name);

	if(graph->node)
	{
		// TODO: traverse the list and free every single node before freeing the list		
		free(graph->node);
	}	
}

void printGraph(graph_t* graph)
{
	LOG_FUNCTION_ENTERING();
	assert(graph != NULL && graph->name != NULL && strlen(graph->name) != 0);

	printf("GRAPH NAME: %s\n", graph->name);

	int i = 0;
	for(i = 0; i < (int)(strlen("GRAPH NAME: ") + strlen(graph->name)); i++)
		printf("-");
	printf("\n");

	if(graph->node == NULL)
	{
		printf("The Graph is empty!!!\n");
		return;
	}

	node_t* currentNode = graph->node;
	while(currentNode != NULL)
	{
		printf("\nNode ID: %d \t \t \t|\n", currentNode->id);
		printf("Node Name: %s \t \t| --> ", currentNode->name);

		interface_t* currentInterface = currentNode->interface;

		while(currentInterface != NULL)
		{
			printf("If%d, %s | --> ", currentInterface->id, currentInterface->name);
			currentInterface = currentInterface->next;
		}

		printf("\n | \t \t \t \t|\n\\_/\n"); // something like a downward arrow
		currentNode = currentNode->next;
	}
	printf("__\n");
}

node_t* createGraphNode(graph_t* graph, char* nodeName) 
{
	LOG_FUNCTION_ENTERING();
	assert(graph != NULL && nodeName != NULL && strlen(nodeName) != 0);

	static unsigned int newNodeID = 0;

	node_t* newNode = (node_t*)calloc(1, sizeof(node_t));
	assert(newNode != NULL);

	newNode->id = ++newNodeID;
	newNode->name = (char*)calloc(1, sizeof(strlen(nodeName) + 1 /*terminal character*/ ));
	assert(newNode->name != NULL);

	strncpy(newNode->name, nodeName, strlen(nodeName));
	newNode->name[strlen(newNode->name)] = '\0';

	if(graph->node == NULL)
	{
		graph->node = newNode;
	}
	else
	{
		node_t* previousNode = NULL;
		node_t* currentNode = graph->node;
		while(currentNode != NULL)
		{
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		previousNode->next = newNode;
	}

	return newNode;
}

interface_t* createNodeInterface(node_t* node, char* interfaceName)
{
	LOG_FUNCTION_ENTERING();
	assert(node != NULL && interfaceName != NULL && strlen(interfaceName) != 0);

	static unsigned int newInterfaceID = 0;

	interface_t* newInterface = (interface_t*)calloc(1, sizeof(interface_t));
	assert(newInterface != NULL);

	newInterface->id = ++newInterfaceID;
	newInterface->name = (char*)calloc(1, sizeof(strlen(interfaceName) + 1 /*terminal character*/));
	assert(newInterface->name != NULL);

	strncpy(newInterface->name, interfaceName, strlen(interfaceName));
	newInterface->name[strlen(newInterface->name)] = '\0';

	newInterface->owningNode = node;

	if(node->interface == NULL)
	{
		node->interface = newInterface;
	}
	else
	{
		interface_t* previousInterface = NULL;
		interface_t* currentInterface = node->interface;
		while(currentInterface != NULL)
		{
			previousInterface = currentInterface;
			currentInterface = currentInterface->next;
		}
		previousInterface->next = newInterface;
	}

	setMacAddrOfInterface(newInterface);

	return newInterface;

}

link_t* createLinkBetweenInterfaces(interface_t* interface1, interface_t* interface2, unsigned int linkCost)
{
	LOG_FUNCTION_ENTERING();
	assert(interface1 != NULL && interface2 != NULL && interface1 != interface2);

	static unsigned int newLinkID = 0;

	link_t* newLink = (link_t*)calloc(1, sizeof(link_t));
	assert(newLink != NULL);

	newLink->id = newLinkID;
	newLink->interface1 = interface1;
	newLink->interface2 = interface2;
	newLink->cost = linkCost;

	interface1->owningLink = newLink;
	interface2->owningLink = newLink;

	return newLink;
}

// nodes should exist, the nodes' interfaces and the their link are created
link_t* insertLinkBetweenNodes(node_t* fromNode, char* fromInterfaceName, node_t* toNode, char* toInterfaceName, unsigned int linkCost)
{
	LOG_FUNCTION_ENTERING();
	assert(fromNode != NULL && fromInterfaceName != NULL && strlen(fromInterfaceName) != 0 && toNode != NULL && toInterfaceName != NULL && strlen(toInterfaceName) != 0);

	interface_t* fromInterface = createNodeInterface(fromNode, fromInterfaceName); // TODO: Maybe check if the node has already an interface with that name 
	assert(fromInterface != NULL);

	interface_t* toInterface = createNodeInterface(toNode, toInterfaceName);
	assert(toInterface != NULL);

	link_t* linkBetween = createLinkBetweenInterfaces(fromInterface, toInterface, linkCost);
	assert(linkBetween != NULL);

	return linkBetween;
}

interface_t* searchNodeForInterfaceByName(node_t* node, char* interfaceName)
{
	LOG_FUNCTION_ENTERING();
	assert(node != NULL && interfaceName != NULL);

	interface_t* currentInterface = node->interface;

	while(currentInterface != NULL)
	{
		if(strcmp(currentInterface->name, interfaceName) == 0)
			return currentInterface;
		currentInterface = currentInterface->next;
	}

	return NULL;
}

node_t* searchGraphForNodeByName(graph_t* graph, char* nodeName)
{
	LOG_FUNCTION_ENTERING();
	assert(graph != NULL && nodeName != NULL);

	node_t* currentNode = graph->node;

	while(currentNode != NULL)
	{
		if(strcmp(currentNode->name, nodeName) == 0)
			return currentNode;
		currentNode = currentNode->next;
	}

	return NULL;
}