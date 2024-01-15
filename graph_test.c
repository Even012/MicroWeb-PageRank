#include <stdio.h>
#include "graph.h"
#include "assert.h"
#include "string.h"
#include "pagerank.h"
#include "dijkstra.h"

int main(void) {
    
    // string s1 = "string 1";
    // string s2 = "string 2";
    // string s3 = "string 3";


    graph g = graph_create();
    // assert(!graph_has_vertex(g, s1));
    // printf("nV:%zu\n", graph_vertices_count(g));

    if (!graph_has_vertex(g, "index")) graph_add_vertex(g, "index");
    if (!graph_has_vertex(g, "X")) graph_add_vertex(g, "X");
    if (!graph_has_vertex(g, "Y")) graph_add_vertex(g, "Y");
    if (!graph_has_vertex(g, "Z")) graph_add_vertex(g, "Z");
    
    graph_add_edge(g, "index", "X", 1);
    graph_add_edge(g, "index", "Y", 1);
    graph_add_edge(g, "index", "Z", 1);
    graph_add_edge(g, "X", "index", 1);
    graph_add_edge(g, "Y", "index", 1);


    graph_worst_path(g, "X", 0.85, 0.00001);
    graph_show_path(g, "Z");

    // graph_show(g, stdout);
    // if (graph_has_edge(g,s1,s2)) printf("s1--s2\n");
    // if (graph_has_edge(g,s2,s1)) printf("s2--s1\n");
    // if (graph_has_edge(g,s2,s2)) printf("s2--s2\n");

    // graph_pagerank(g, 0.85, 0.00001);
    // graph_show_pagerank(g, stdout);
    
    // graph_add_vertex(g, s1);
    // assert(graph_has_vertex(g, s1));
    // printf("nV:%zu\n", graph_vertices_count(g));
 
    // // error here
    // graph_add_vertex(g, s2);
    // assert(graph_has_vertex(g, s2));
    // printf("nV:%zu\n", graph_vertices_count(g));

    
    // graph_add_vertex(g, s3);
    // assert(graph_has_vertex(g, s3));
    // printf("nV:%zu\n", graph_vertices_count(g));

    // printf("nE of s1:%zu\n", graph_edges_count(g, s1));
    // printf("nE of s2:%zu\n", graph_edges_count(g, s2));

    // graph_add_edge(g, s1, s2, 0.5);
    // assert(graph_has_edge(g, s1, s2));
    // double w = graph_get_edge(g,s1,s2);
    // printf("%0.3f\n", w);

    // graph_add_edge(g, s2, s1, 0.5);
    // assert(graph_has_edge(g, s2, s1));
    // w = graph_get_edge(g,s2,s1);
    // printf("%0.3f\n", w);

    // graph_add_edge(g, s3, s1, 0.5);
    // graph_add_edge(g, s3, s2, 0.5);

    // graph_update_edge(g,s1,s2,0.6);
    // assert(graph_has_edge(g, s1, s2));
    // w = graph_get_edge(g,s1,s2);
    // printf("%0.3f\n", w);

    // graph_update_edge(g,s2,s3,0.8);
    // assert(graph_has_edge(g, s2, s3));
    // w = graph_get_edge(g,s2,s3);
    // printf("%0.3f\n", w);

    // printf("nE of s1:%zu\n", graph_edges_count(g, s1));
    // printf("nE of s2:%zu\n", graph_edges_count(g, s2));
    // printf("nE of s3:%zu\n", graph_edges_count(g, s3));

    // graph_show(g, stdout);

    printf("all tests passed.\n");
    graph_destroy(g);

    return 0;
}