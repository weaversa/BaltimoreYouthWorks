#ifndef DIGRAPH_H
#define DIGRAPH_H

#include "youthworks.h"

typedef struct edge_t {
  uint32_t sink;
  int32_t weight;
} edge_t;

create_list_headers(edges_t, edge_t *)

typedef struct digraph_t {
  uint8_t use_soft_constraints;
  uint32_t nNumSourceNodes;
  edges_t **edges; //index into a list of edges for every node.
                  //e.g. edges[0] -> list of edges going out from node 0
} digraph_t;

uint32_t *print_digraph(FILE *fout, digraph_t *pDigraph, youths_t *youths, jobs_t *jobs);
digraph_t *create_digraph(youths_t *youths, jobs_t *jobs, uint8_t use_soft_constraints);
void digraph_free(digraph_t *pDigraph);

#endif
