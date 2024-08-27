#ifdef GRAPH_H
#define GRAPH_H

typedef struct interface interface_t;
typedef struct node node_t;

typedef struct link
{
	unsigned int id;
	interface_t* interf1;
	interface_t* interf2;
} link_t;

typedef struct interface
{
	unsigned int id;
	char* name;
	node_t* owningNode;
	link_t* owningLink;
	unsigned int cost; // maybe of no use for now
} interface_t;

typedef struct interfaceList
{
	interface_t* interface;
	interface_t* next;
} interfaceList_t;

typedef struct node
{
	unsigned int id;
	char* name;
	interfaceList_t* interface;
} node_t;

typedef struct nodeList
{
	node_t* node;
	node_t* next;
} nodeList_t;

typedef struct graph
{
	char* name;
	nodeList_t* node;
} graph_t;

static inline node_t* getInterfaceOwningNode(interface_t* interface)
{
#ifdef DEBUG_MODE
	if(interface)
#endif

	return interface->owningNode;

#ifdef DEBUG_MODE
	else
	{
		fprintf(stderr, "getOwningNode(): Error, NULL argument!\n");
		return NULL;
	}
#endif
}

#endif