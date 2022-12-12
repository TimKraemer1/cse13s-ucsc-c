#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//Path struct declaration is from the assignment pdf

struct Path {
    Stack *vertices;
    uint32_t length;
};

//create path by allocation and create a stack
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

// delete the stack by free memory of the path and the stack, set p to NULL
void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);
    free(*p);
    *p = NULL;
    return;
}

//push a vertex onto path, return if successful
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {

    if (v < VERTICES && v >= 0) {
        if (stack_size(p->vertices) == 0) {
            stack_push(p->vertices, v);
            return true;
        } else if (stack_size(p->vertices) > 0 && stack_size(p->vertices) <= VERTICES) {
            uint32_t temp_value = 1;
            uint32_t *top_vertex;
            top_vertex = &temp_value;
            stack_peek(p->vertices, top_vertex);
            stack_push(p->vertices, v);
            p->length += graph_edge_weight(G, *top_vertex, v);
            return true;
        } else {
            return false;
        }

    } else {
        return false;
    }
}

//pop the top vertex from the path, return if successful
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {

    bool bool_result;
    if (stack_size(p->vertices) == 0) {
        bool_result = false;
    } else if (stack_size(p->vertices) == 1) {
        stack_pop(p->vertices, v);
        bool_result = true;
    } else if (stack_size(p->vertices) > 1) {
        stack_pop(p->vertices, v);

        uint32_t temp_value = 1;
        uint32_t *stack_top;
        stack_top = &temp_value;

        stack_peek(p->vertices, stack_top);
        p->length -= graph_edge_weight(G, *stack_top, *v);
        bool_result = true;
    } else {
        bool_result = false;
    }
    return bool_result;
}

//returns the number of vertices in the path
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

//return the length of the path
uint32_t path_length(Path *p) {
    return p->length;
}

//copy the path from src to dst
void path_copy(Path *dst, Path *src) {
    dst->length = src->length;
    stack_copy(dst->vertices, src->vertices);
}

//print path length and print stack to outfile
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %u\n", path_length(p));
    stack_print(p->vertices, outfile, cities);
}
