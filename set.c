// TODO: Add any extra #includes that you need

#include "set.h"
#include <assert.h>
#include <stdlib.h> 
#include <string.h>

// TODO: Add your data structure definitions
typedef struct Node {
   string data;
   struct Node *next;
} Node;

typedef struct SetRepr{
    Node *head;         
} SetRepr;

Node *makeNodeSet(string dat) {
   Node *new = malloc(sizeof(Node));
   assert(new != NULL);
   string data = malloc(strlen(dat)*sizeof(char) + 1);
   assert(data != NULL);
   strcpy(data, dat);
   new->data = data;       // initialise data
   new->next = NULL;    // initialise link to next node
   return new;          // return pointer to new node
}



// TODO: Fill in these function stubs

set set_create() {
    set s = malloc(sizeof(SetRepr));
    assert(s != NULL);
    s->head = NULL;
    return s;
}

void set_destroy(set s) {
    assert(s != NULL);
    while (s->head) {
        Node *p = s->head;
        s->head = s->head->next;
        free(p);       
    }
    free(s);
}

void set_insert(set s, string dat) {
    assert(s != NULL);
    // only insert if it does not exist
    Node *p = s->head;
    while (p) {
        if (!strcmp(p->data, dat)) {
            break;
        }        
        p = p->next;
    }
// 1 0-1-0
// n      ^
    if (!p) {
        Node *new = makeNodeSet(dat);
        new->next = s->head;
        s->head = new;
    }

}
// 0
// p q 
void set_remove(set s, string dat) {
    // only remove if it does exist
    assert(s != NULL);
    assert(s->head != NULL);

    Node *p = s->head;    
    if (!strcmp(p->data, dat)) {
        s->head = s->head->next;
        free(p);
    }else {
        Node *q = p->next;
        while (q) {
            if (!strcmp(q->data, dat)) {
                break;
            }
            p = p->next;
            q = p->next;       
        }
        if (q) {
            p->next = q->next;
            free(q);
        }   
    }
}

bool set_contains(set s, string dat) {
    // TODO: Delete the code below when you're ready to implement this function
    assert(s != NULL);  
    Node *p = s->head;
    while (p) {
        if (!strcmp(p->data, dat)) {
            break;
        }
        p = p->next;

    }
    if (p) {
        return true;
    } else {
        return false;
    }
}
