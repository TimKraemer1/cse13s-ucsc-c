#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//graph struct, graph create, graph delete are all from the assignment pdf

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

//create graph struct, allocate memory forthe graph
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

//delete graph, free mem and set G to NULL
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

//return number of vertices in graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

//add and edge to graph from i to j with weight k, return if successful
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if ((i < VERTICES && j < VERTICES) && (i >= 0 && j >= 0)
        && (i <= G->vertices && j <= G->vertices) && (k > 0)) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return true;
    } else {
        return false;
    }
}

//check if graph G has an edge between i and j, return if it has or not
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i < VERTICES && j < VERTICES && G->matrix[i][j] > 0) {
        return true;
    } else {
        return false;
    }
}

//return the edge weight between i and j
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i < VERTICES && j < VERTICES && G->matrix[i][j] > 0) {
        return G->matrix[i][j];
    } else {
        return 0;
    }
}

//check if a vertex v has been marked visited, bool visited array has if each vertex is visted or
//not
bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v]) {
        return true;
    } else {
        return false;
    }
}

//mark the vertex v in the graph visited (using bool visited array)
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
}

//mark vertex v unvisited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
}
