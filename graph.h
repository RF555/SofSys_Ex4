#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "edges.h"
#include "nodes.h"

typedef struct Graph {
    p_node n_root;
    p_node n_tail;
    int node_size;
    int edge_size;
} graph, *p_graph;

graph *init_graph();
int add_node(graph *g, int id, edge_list *pe_list);
int remove_node(graph *g, int id);
int add_edge(graph *g, int src, float w, int dest);
int add_Edge(graph *g, edge *e);
int remove_edge(graph *g, int src, int dest);


#endif //_GRAPH_H_