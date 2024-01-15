// TODO: Add any extra #includes that you need

#include "pqueue.h"
#include <assert.h>
#include <stdlib.h> 
#include <string.h>

// TODO: Add your data structure definitions
typedef struct NodePQ {
   string data;
   double priority;
   struct NodePQ *next;
} NodePQ;

typedef struct PriorityQueueRepr{
    NodePQ *head;
    NodePQ *tail;
} PriorityQueueRepr;

NodePQ *makeNodePQ(string dat, double prio) {
   NodePQ *new = malloc(sizeof(NodePQ));
   assert(new != NULL);
   string data = malloc(strlen(dat)*sizeof(char)+1);
   assert(data != NULL);
   strcpy(data, dat);
   new->data = data;       // initialise data
   new->priority = prio;
   new->next = NULL;    // initialise link to next node
   return new;          // return pointer to new node
}



// TODO: Fill in these function stubs


pqueue pqueue_create() {
    pqueue pq = malloc(sizeof(PriorityQueueRepr));
    assert(pq != NULL);
    pq->head = NULL;
    pq->tail = pq->head;
    return pq;
}

void pqueue_destroy(pqueue pq) {
    assert(pq != NULL);
    while (pq->head) {
        NodePQ *p = pq->head;
        pq->head = pq->head->next;
        free(p);
    }
    free(pq);
}

void pqueue_join(pqueue pq, string dat, priority prio) {
    NodePQ *new = makeNodePQ(dat, prio);
    if (!pq->tail) {
        pq->tail = new;
        pq->head = pq->tail;
    } else {
        pq->tail->next = new;
        pq->tail = pq->tail->next;
    }
}

// 0 0 0 0
//       ^

string pqueue_leave(pqueue pq) {
    assert(pq != NULL);    
    assert(pq->head != NULL);
    NodePQ *i = pq->head;  
    double min = pq->head->priority;
    while (i) {
        if (i->priority < min) {
            min = i->priority;
        }
        i = i->next; 
    }
    // after we get min prio
    i = pq->head;
    NodePQ *p = NULL;
    NodePQ *q = pq->head;    
    while (i) {
        if (i->priority == min) {
            q = i;
            break;
        }
        p = i;
        i = i->next; 
    }

    if (pq->head->next == NULL) {
        q = pq->head;
        pq->head = NULL;
        pq->tail = NULL;
    } else {
        if (pq->head->priority == min) {
            pq->head = pq->head->next;
        } else if (pq->tail->priority == min) {
            p->next = q->next;   
            pq->tail = p;
        } else {
            p->next = q->next;            
        }
    }
    return q->data;
}

string pqueue_peek(pqueue pq) {
    assert(pq != NULL);    
    assert(pq->head != NULL);
    NodePQ *p = pq->head;
    double min = pq->head->priority;
    NodePQ *q = pq->head;
    while (p) {
        if (p->priority < min) {
            min = p->priority;
            q = p;
        }
        p = p->next; 
    }
    return q->data;
}

bool pqueue_empty(pqueue pq) {
    // TODO: Delete the code below when you're ready to implement this function
    if (!pq->tail) {
        return true;
    }else {
        return false;
    }
}
