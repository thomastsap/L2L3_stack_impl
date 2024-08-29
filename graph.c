#include <stdio.h>
#undef NDEBUG // when defined, remove assertions from code
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"
#include "util.h"

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

	graph_t* graph = (graph_t*)malloc(sizeof(graph_t));
	assert(graph != NULL);

	graph->name = (char*)malloc(strlen(topologyName) + 1 /*terminal char*/ );
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

	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	assert(newNode != NULL);

	newNode->id = ++newNodeID;
	newNode->name = (char*)malloc(sizeof(strlen(nodeName) + 1 /*terminal character*/ ));
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

	interface_t* newInterface = (interface_t*)malloc(sizeof(interface_t));
	assert(newInterface != NULL);

	newInterface->id = ++newInterfaceID;
	newInterface->name = (char*)malloc(sizeof(strlen(interfaceName) + 1 /*terminal character*/));
	assert(newInterface->name != NULL);

	strncpy(newInterface->name, interfaceName, strlen(interfaceName));
	newInterface->name[strlen(newInterface->name)] = '\0';

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

	return newInterface;

}

/*void insertLinkBetweenNodes(node_t* fromNode, char* fromInterfaceName, node_t* toNode, char* toInterfaceName, unsigned int linkCost)
{
	LOG_FUNCTION_ENTERING();
	assert(fromNode != NULL && fromInterfaceName != NULL && strlen(fromInterfaceName) != 0 && toNode != NULL && toInterfaceName != NULL && strlen(toInterfaceName) != 0);

	static unsigned int newInterfaceID = 0;

	interface_t* newInterface = (interface*)malloc(sizeof(interface_t));
	assert(newInterface != NULL);

	newInterface->id = ++newInterfaceID;


}*/

int main(void)
{
	graph_t* newGraph = createNewGraph("NewGraph");
	node_t* node1 = createGraphNode(newGraph, "thomas1");
	createNodeInterface(node1, "if1");
	createNodeInterface(node1, "if2");
	createNodeInterface(node1, "if3");
	node_t* node2 = createGraphNode(newGraph, "thomas2");
	createNodeInterface(node2, "if4");
	createNodeInterface(node2, "if5");
	node_t* node3 = createGraphNode(newGraph, "thomas3");
	createNodeInterface(node3, "if6");
	node_t* node4 = createGraphNode(newGraph, "thomas4");
	printGraph(newGraph);
	return 0;
}