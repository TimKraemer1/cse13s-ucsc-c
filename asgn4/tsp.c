#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"

static uint32_t recursive_counter = 0;
static uint32_t smallest_length = UINT_MAX;

//dfs influenced by the pseudocode included in the pdf document

void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool is_v) {
    recursive_counter += 1;
    //we mark the current vertex as visited and add it to our current path
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);

    //now we check if the current path we have is full and there is an edge from the last vertex to
    //the first one, and if it is add the first path to the end to make a complete loop
    if (path_vertices(curr) == graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {

        path_push_vertex(curr, START_VERTEX, G);
        //checking if verbose printing is on so that it prints the full path to the output file
        if (is_v) {
            path_print(curr, outfile, cities);
        }
        //next we check to see if it is the shortest path. If it is, change smallest length to
        //current path's length, and the copy the current path to the shortest path
        if (path_length(curr) < smallest_length) {
            smallest_length = path_length(curr);
            path_copy(shortest, curr);
        }
        //remove the first vertex from the end of the path
        uint32_t temp = 0;
        path_pop_vertex(curr, &temp, G);
        //if the path is not full or there is no edge between the latest vertex and the start, we
        //check to see if our current path is too big to be the shortest path anyway
    } else if (path_length(curr) < smallest_length) {

        //if it is still possible for it to be the smallest path, cycle through neighboring nodes
        //that havent been visited yet and recursively call each of them
        for (uint32_t w = START_VERTEX; w < graph_vertices(G); w++) {
            if (graph_has_edge(G, v, w)) {
                if (!(graph_visited(G, w))) {
                    dfs(G, w, curr, shortest, cities, outfile, is_v);
                }
            }
        }
    }

    //after all is checked and done, remove the current vertex from the path
    graph_mark_unvisited(G, v);
    path_pop_vertex(curr, &v, G);
}
//optarg that looks at user input
int main(int argc, char **argv) {
    int opt;
    bool is_h = false;
    bool is_u = false;
    bool is_i = false;
    bool is_v = false;
    bool is_o = false;

    //we create empty char arrays to store the name of our in and out files
    char in[4096];
    char out[4096];

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': is_h = true; break;
        case 'v': is_v = true; break;
        case 'u': is_u = true; break;
        case 'i':
            is_i = true;
            strcpy(in, optarg);
            break;
        case 'o':
            is_o = true;
            strcpy(out, optarg);
            break;
        }
    }

    //create outfile as stdout, and if is_o is on then switch it to out as a writeable open file
    FILE *outfile = stdout;
    if (is_o) {
        outfile = fopen(out, "w");
    }

    //checks to see if -h was used, and if it was, print the help message, close the file, and exit
    //the program
    if (is_h) {
        fprintf(stdout,
            "SYNOPSIS\nTraveling Salesman Problem using DFS.\n\nUSAGE\n./tsp [-u] [-v] "
            "[-h] [-i infile] [-o outfile]\n\nOPTIONS\n-u             Use undirected "
            "graph.\n-v             Enable verbose printing.\n-h             Program "
            "usage and help.\n-i infile      Input containing graph (default: stdin)\n-o "
            "outfile     Output of computed path (default: stdout)\n");
        fclose(outfile);
        exit(0);
    }
    //creates infile as stdin, and if is_i is on then switch it to in as a readable open file
    FILE *infile = stdin;
    if (is_i) {
        infile = fopen(in, "r");
    }

    //file reading input inspired by TA Eugene's demonstration

    //scan in the number of vertices
    uint32_t vertices = 0;
    fscanf(infile, "%" SCNu32 "\n", &vertices);

    //create a new graph with size vertices to store our edges in it
    Graph *new_graph;
    new_graph = graph_create(vertices, is_u);

    //read cities; creates a char pointer array, increment through file and use fgets to grab each
    //city string, allocate a pointer named buf and set it equal to temp to keep the original
    //pointed location, store city name in buf, seperate from the \n character at the end, and
    //duplicate it into the cities char array. Then free temp (from original pointed location)
    char *cities[vertices];
    for (uint32_t i = 0; i < vertices; i++) {
        char *buf = (char *) malloc(1024);
        char *temp = buf;
        fgets(buf, 1024, infile);
        cities[i] = strdup(strsep(&buf, "\n"));
        free(temp);
    }

    //read the tuples using fscanf
    uint32_t a = 0, b = 0, c = 0;
    while (fscanf(infile, "%" SCNu32 " %" SCNu32 " %" SCNu32 "\n", &a, &b, &c) != EOF) {
        graph_add_edge(new_graph, a, b, c);
    }
    //close the infile since we are done reading it
    fclose(infile);

    //create all of the Paths, current and shortest
    Path *current_path;
    current_path = path_create();
    Path *shortest_path;
    shortest_path = path_create();

    //if the number of vertices is 1 or less, print message, else, run dfs and print the shortest
    //path to outfile
    if (vertices <= 1) {
        fprintf(outfile, "There's nowhere to go.\n");
    } else {
        dfs(new_graph, START_VERTEX, current_path, shortest_path, cities, outfile, is_v);
        //print the number of recursive calls from static variable
        path_print(shortest_path, outfile, cities);
        fprintf(outfile, "Recursive Calls: %u\n", recursive_counter);
    }

    //we close the outfile
    fclose(outfile);

    //free allocated memory
    path_delete(&current_path);
    graph_delete(&new_graph);
    path_delete(&shortest_path);

    for (uint32_t i = 0; i < vertices; i++) {
        free(cities[i]);
    }
}
