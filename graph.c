// TODO: Add any extra #includes that you need

#include "graph.h"
#include "pagerank.h"
#include "dijkstra.h"
#include "string.h"
#include <stdlib.h>
#include "assert.h"
#include <math.h>
#include <stdbool.h>
#include "pqueue.h"
#include "stack.h"

#define VERY_HIGH_VALUE 999999

// TODO: Add your data structure definitions
typedef struct Node {
   string data;
   weight Weight;
   double oldrank;
   double pagerank;
   struct Node *next; 
   struct Node *neighbour;
   struct Node *pred;
   double dist;
   bool vSet;
} Node;


typedef struct GraphRepr {
   Node *head;  
   int nV;     // #vertices
   int nE;     // #edges
} GraphRepr;

Node *makeNodeGraph(string dat, weight w) {
    // string is a pointer, but weight is not.
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);   
    string data = malloc(strlen(dat)*sizeof(char)+1);
    assert(data != NULL);  // do we need to free data here?
    strcpy(data,dat);
    new->data = data;       // initialise data
    new->Weight = w;
    new->next = NULL;    // initialise link to next node
    new->neighbour = NULL;
    return new;          // return pointer to new node
}


// TODO: Fill in these function stubs
graph graph_create(void) {
    graph g = malloc(sizeof(GraphRepr));
    assert(g != NULL);
    g->nV = 0;
    g->nE = 0;
    g->head = NULL;
    // g->Pedge = NULL;
    return g;
}

void graph_destroy(graph g) {
    assert(g != NULL);
    // free nodes and edges
    Node *p = g->head; 
    while (p) {
        Node *q = p;
        p = p->neighbour;
        while (q) {
            Node *s = q;
            q = q->next;
            // free(s->data);
            free(s);
        }
        
    }
    // free graph
    free(g);
}

void graph_add_vertex(graph g, string v) {
    if (g->head == NULL) {
        Node *new = makeNodeGraph(v, 0.0);
        g->head = new;
        g->nV = 1;
    } else {
        Node *p = g->head;
        bool flag = false;   //graph has vertex      
        while (p) {
            // if exists
            if (!strcmp(p->data, v)) {
                flag = true;
                break;
            }
            // if not exists
            if (p->neighbour == NULL) {
                break;
            }
            p = p->neighbour;
        }

        if (!flag) {        
            Node *new = makeNodeGraph(v, 0.0);  
            p->neighbour = new;   
            g->nV++;        
        }   
    }
}

bool graph_has_vertex(graph g, string v) {
    Node *p = g->head;   
    while (p) {
        if (!strcmp(p->data, v)) {
            return true;
        }
        p = p->neighbour;

    }

    return false;
}

size_t graph_vertices_count(graph g) {
    return g->nV;
}


void graph_add_edge(graph g, string v1, string v2, weight w) {
    assert(g != NULL && graph_has_vertex(g, v1) && graph_has_vertex(g, v2));
    // locate v1 as p
    Node *p = g->head;     
    while (p) {
        if (!strcmp(p->data, v1)) {
            break;
        }
        p = p->neighbour;
    }

    // use p as source to traverse
    bool flag = false;   //graph has edge 
    while(p != NULL) {
        //v2 exists
        if (!strcmp(p->data, v2)) {
            flag = true;   //graph has edge 
            break;
        }
        // v2 not exists
        if (p->next == NULL) {
            break;
        }
        p = p->next;
    }

    // v2 not exists
    if (!flag) {
        Node *new = makeNodeGraph(v2, w);
        p->next = new;
        g->nE++;
    }
}

bool graph_has_edge(graph g, string v1, string v2) {
    assert(g != NULL && graph_has_vertex(g, v1) && graph_has_vertex(g, v2));
    // locate v1 as p
    Node *p = g->head;     
    while (p) {
        if (!strcmp(p->data, v1)) {
            break;
        }
        p = p->neighbour;
    }

    // use p as source to traverse
    p = p->next;
    while(p != NULL) {
        //v2 exists
        if (!strcmp(p->data, v2)) {
            return true;
        }
        // v2 not exists
        p = p->next;
    }
    return false;
}

void graph_update_edge(graph g, string v1, string v2, weight w) {
    assert(g != NULL && graph_has_vertex(g, v1) && graph_has_vertex(g, v2));
    // locate v1 as p
    Node *p = g->head;     
    while (p) {
        if (!strcmp(p->data, v1)) {
            break;
        }
        p = p->neighbour;
    }

    // use p as source to traverse
    bool flag = false;   //graph has vertex 
    while(p != NULL) {
        //v2 exists
        if (!strcmp(p->data, v2)) {
            p->Weight = w;
            flag = true;   //graph has edge
        }
        // v2 not exists
        if (p->next == NULL) {
            break;
        }
        p = p->next;
    }

    // v2 not exists
    if (!flag) {
        Node *new = makeNodeGraph(v2, w);
        p->next = new;
        g->nE++;
    }
}

weight graph_get_edge(graph g, string v1, string v2) {
    assert(g != NULL && graph_has_vertex(g, v1) && graph_has_vertex(g, v2));
    // locate v1 as p
    Node *p = g->head;     
    while (p) {
        if (!strcmp(p->data, v1)) {
            break;
        }
        p = p->neighbour;
    }

    // use p as source to traverse
    while(p != NULL) {
        //v2 exists
        if (!strcmp(p->data, v2)) {
            return p->Weight;
        }
        // v2 not exists
        p = p->next;
    }
    return 0;
}

size_t graph_edges_count(graph g, string v) {
    int count = 0;
    Node *p = g->head; 
    while (p) {
        Node *q = p;
        p = p->neighbour;
        if (!strcmp(q->data,v)) {
            q = q->next;
            while (q){
                count++;
                q = q->next;
            }
        } else {
            while (q) {
                Node *s = q;   
                q = q->next;                     
                if (!strcmp(s->data,v)) {
                    count++;
                }
            }
        }
    }
    return count;
}

void graph_show(graph g, FILE *output) {

    Node *p = g->head; 
    // print vertex
    while (p) {
        if (output == NULL) {
            printf("%s\n", p->data); 
        } else {
            fprintf(output, "%s\n", p->data); 
        }   
        p = p->neighbour; 
    }
    // print edges
    p = g->head; 
    while (p) {
        Node *q = p->next;
        while (q) {  
            if (output == NULL) {
                printf("%s %s %.3f\n", p->data, q->data, graph_get_edge(g, p->data, q->data));
            } else {
                fprintf(output, "%s %s %.3f\n", p->data, q->data, graph_get_edge(g, p->data, q->data));
            }                     
            q = q->next;
        }
        p = p->neighbour;
    }
}

void graph_pagerank(graph g, double damping, double delta) {
    double sink_rank = 0;
    bool flag = true;
    int N = g->nV;
    Node *p = g->head; 
    Node *I = g->head;
    Node *s = g->head; 
    int outdegree = 0;
    // initialize and record (pr-or > delta or not)
    while (p) {
        p->oldrank = 0.0;
        p->pagerank = 1.0 / N;
        p = p->neighbour; 
    }

    while (flag) {
        p = g->head; // update oldrank of all vertices
        while (p) {         
            p->oldrank = p->pagerank;
            p = p->neighbour; 
        }
        sink_rank = 0;
        p = g->head;  // no outbound edge: added to sink
        while (p) {
            if (!p->next) {
                sink_rank += damping*(p->oldrank/N);
            }
            p = p->neighbour; 
        }
        // printf("sink_rank: %0.3f\n", sink_rank);
        p = g->head;    // vertices with outbound edges
        while (p) {
            p->pagerank = sink_rank + ((1-damping)/N);
            // printf("pos1: %s (%0.3f)\n", p->data, p->pagerank);
            I = g->head;
            while (I) {
                if (graph_has_edge(g,I->data,p->data)) {  
                    outdegree = 0;
                    s = I->next; 
                    while (s) {                  
                        outdegree++;
                        s = s->next;                    
                    }                
                    p->pagerank += (damping*(I->oldrank))/outdegree;
                    // printf("pos2: %s to %s (%0.3f)  degree:%d\n", I->data, p->data, p->pagerank, outdegree);
                }
                // printf("degree: %zu\n", graph_edges_count(g,I->data));
                // printf("add: %0.3f\n", (damping*(I->oldrank))/graph_edges_count(g,I->data));
                I = I->neighbour;
            }   
            p = p->neighbour; 
        }

        p = g->head;
        while (p) {
            // printf("pos3: %s pr:(%lf) or:(%lf)\n", p->data, p->pagerank, p->oldrank);
            p = p->neighbour; 
        }
        // check continue or not
        // i--;
        flag = false;
        p = g->head;
        while (p) {
            // printf("pagerank(%0.3f) - oldrank(%0.3f)\n", p->pagerank, p->oldrank);
            if (p->pagerank - p->oldrank > delta) {
                flag = true;
                break;
            }
            p = p->neighbour; 
        }
    }
    // round every pagerank
    p = g->head;
    while (p) {
        p->pagerank = round(p->pagerank  * 1000) / 1000;
        // printf("%s %f\n", p->data, p->pagerank);
        p = p->neighbour; 
    }
}

void graph_show_pagerank(graph g, FILE *file) {
    // from highest pagerank to the lowest
    Node *sorted = NULL;

    Node *current = g->head;
    while (current) {
        Node *neighbour = current->neighbour;
        Node *newnode = current;
        if (sorted == NULL || sorted->pagerank < newnode->pagerank || 
        ((sorted->pagerank == newnode->pagerank)&& strcmp(sorted->data, newnode->data)<0)) {
            newnode->neighbour = sorted;
            sorted = newnode;
        }
        else {
            current = sorted;
            /* Locate the node before the point of insertion */
            while (current->neighbour != NULL
                && (current->neighbour->pagerank > newnode->pagerank
                || ((current->neighbour->pagerank == newnode->pagerank)
                && strcmp(current->neighbour->data, newnode->data)<0)
                    ) 
                ) {
                current = current->neighbour;
            }
            newnode->neighbour = current->neighbour;
            current->neighbour = newnode;
        }
        current = neighbour;
    }
    g->head = sorted;
    current = g->head;
    while (current) {
        if (file == NULL) {
            printf("%s (%.3f)\n", current->data, current->pagerank);
        } else {
            fprintf(file, "%s (%.3f)\n", current->data, current->pagerank); 
        }   
        
        current = current->neighbour; 
    }
}

void graph_worst_path(graph g, string source, double damping, double delta) {
    // first, get pagerank and update weight
    graph_pagerank(g, damping, delta);
    Node *p = g->head; 
    while (p) {
        Node *q = p->next;
        while (q) {
            graph_update_edge(g, p->data, q->data, q->pagerank);
            q = q->next;
        }
        p = p->neighbour;
    }
    // SSSP initialization
    pqueue pq = pqueue_create();
    p = g->head;
    while (p) {
        p->pred = NULL;
        p->dist = VERY_HIGH_VALUE;
        p->vSet = true;
        if (!strcmp(p->data, source)) {
            p->dist = 0;
        }
        pqueue_join(pq, p->data, p->dist);   // prio ==  p->dist
        p = p->neighbour;
    }
    // after initial
    int flag = 1;
    string bestVertex;
    Node *bestNode = NULL;                 // get bestNode
    while (flag) {
        /* get minimum element in dist */
        bestVertex = pqueue_leave(pq);  // pop source first
        p = g->head;
        while (p) {
            if (!strcmp(bestVertex, p->data)){
                bestNode = p;
                break;
            }
            p = p->neighbour;
        }
        /* relax edge */
        p = g->head;
        double wt;
        while (p) {
            // printf("%d\n", (int)p->vSet);
            if (p->vSet == false) {
                p = p->neighbour;
                continue;
            }
            wt = graph_get_edge(g, bestVertex, p->data);    // check if weight > 0
            // printf("%s--%s: %.3f\n", bestNode->data, p->data, wt);
            if ( wt && bestNode->dist + wt < p->dist) {
                // printf("%s--%s: %.3f\n", p->data, bestNode->data, wt);
                p->dist = bestNode->dist + wt;
                p->pred = bestNode;
            }
            p = p->neighbour;
        }
        bestNode->vSet = false;
        /* check continue or not */
        flag = 0;
        p = g->head;
        while (p) {
            if (p->vSet == true) {
                flag = 1;
                break;
            }
            p = p->neighbour;
        }
    }
    pqueue_destroy(pq);

}

// X - Z (given source and destination)
void graph_show_path(graph g, string destination) {
    Node *p = g->head;
    while (p) {
        if (!strcmp(p->data, destination)) {
            break;
        }
        p = p->neighbour;
    }  

    if (p->dist == VERY_HIGH_VALUE) {
        printf("No path found.\n");
    }else {   
        stack s = stack_create();
        while(p) {
            stack_push(s, p->data);
            p = p->pred;
        }
        // print
        printf("%s\n", stack_pop(s));
        while (!stack_empty(s)) {
            printf("-> %s\n", stack_pop(s));
        } 
        stack_destroy(s);
    }   
}


