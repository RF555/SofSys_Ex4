#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "edges.h"
#include "nodes.h"

typedef struct Graph {
    node_arr nodes;
    edge_arr edges;
    int node_size;
    int edge_size;
} graph, *p_graph;

void init_graph();

void add_node(graph *g, int id);

void remove_node(graph *g, int id);

void add_edge(graph *g, int src, float w, int dest);

void add_Edge(graph *g, edge e);

void remove_edge(graph *g, int src, int dest);


#endif //_GRAPH_H_