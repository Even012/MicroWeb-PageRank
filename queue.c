// TODO: Add any extra #includes that you need

#include "queue.h"
#include <assert.h>
#include <stdlib.h> 
#include <string.h>
// TODO: Add your data structure definitions
// typedef struct QueueRepr *queue;
typedef struct Node {
   string data;
   struct Node *next;
} Node;

typedef struct QueueRepr{
    Node *head;
    Node *tail;
} QueueRepr;

Node *makeNodeQueue(string dat) {
   Node *new = malloc(sizeof(Node));
   assert(new != NULL);   
   string data = malloc(strlen(dat)*sizeof(char)+1);
   assert(data != NULL);
   strcpy(data,dat);
   new->data = data;       // initialise data
   new->next = NULL;    // initialise link to next node
   return new;          // return pointer to new node
}


// 0-0-0-0
//         ^
// TODO: Fill in these function stubs
queue queue_create() {
    queue q = malloc(sizeof(QueueRepr));
    assert(q != NULL);
    q->head = NULL;
    q->tail = q->head;
    return q;
}

void queue_destroy(queue q) {
    assert(q != NULL);
    while (q->head) {
        Node *p = q->head;
        q->head = q->head->next;
        free(p);
    }
    free(q);
}
//    1  1  0
//    ^     ^  
void queue_enqueue(queue q, string dat) {
    Node *new = makeNodeQueue(dat);
    if (!q->tail) {
        q->tail = new;
        q->head = q->tail;
    } else {
        q->tail->next = new;
        q->tail = q->tail->next;
    }

}
//  0-0-0-0
//        ^
string queue_dequeue(queue q) {
    assert(q->head != NULL);
    Node *out = q->head;
    q->head = q->head->next;
    if (!q->head) {
        q->tail = q->head;
    }
    string data = malloc(sizeof(string));
    data = out->data;
    return data;
}

string queue_peek(queue q) {
    assert(q->head != NULL);
    string data = malloc(sizeof(string));
    data = q->head->data;
    return data;
}

bool queue_empty(queue q) {
    if (!q->tail) {
        return true;
    }else {
        return false;
    }
}
