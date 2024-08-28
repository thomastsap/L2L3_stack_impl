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

	graph->nodeList = (nodeList_t*)malloc(sizeof(nodeList_t));
	assert(graph->nodeList != NULL);
	memset(graph->nodeList, 0, sizeof(nodeList_t));

	return graph;
}

void freeGraph(graph_t* graph)
{
	LOG_FUNCTION_ENTERING();
	assert(graph != NULL);

	if(graph->name)
		free(graph->name);

	if(graph->nodeList)
	{
		// TODO: traverse the list and free every single node before freeing the list		
		free(graph->nodeList);
	}	
}

node_t* createGraphNode(graph_t* graph, char* nodeName) 
{
	LOG_FUNCTION_ENTERING();
	assert(graph != NULL && graph->nodeList != NULL && nodeName != NULL &&
			strlen(nodeName) != 0);

	static int newNodeID = 0;

	node_t* newNode = (node_t*)malloc(sizeof(newNode));
	assert(newNode != NULL);

	newNode->id = ++newNodeID;
	newNode->name = (char*)malloc(sizeof(strlen(nodeName) + 1 /*terminal character*/ ));
	assert(newNode->name != NULL);

	strncpy(newNode->name, nodeName, strlen(nodeName));
	newNode->name[strlen(newNode->name)] = '\0';

	newNode->interfaceList = (interfaceList_t*)malloc(sizeof(interfaceList_t));
	memset(newNode->interfaceList, 0, sizeof(interfaceList_t));

	// TODO: Find empty spot on graph and insert the new node there

	return newNode;
}

int main(void)
{
	graph_t* newGraph = createNewGraph("NewGraph");
	printf("new graph name=%s\n", newGraph->name);
	return 0;
}