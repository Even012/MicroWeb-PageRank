// TODO: Add any extra #includes that you need

#include "stack.h"
#include <assert.h>
#include <stdlib.h> 
#include <string.h>

// TODO: Add your data structure definitions
typedef struct Node {
   string data;
   struct Node *next;
} Node;

typedef struct StackRepr{
    Node *top;
} StackRepr;

Node *makeNodeStack(string dat) {
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


stack stack_create() {
    stack s = malloc(sizeof(StackRepr));
    assert(s != NULL);
    s->top = NULL;
    return s;
}

// 0-0-0-0|
//         ^
void stack_destroy(stack s) {
    assert(s != NULL);
    while (s->top) {
        Node *p = s->top;
        s->top = s->top->next;
        free(p);       
    }
    free(s);
}
// 1 0-0-0-0|
// ^
// 1 |
//   ^
void stack_push(stack s, string dat) {
    Node *new = makeNodeStack(dat);
    new->next = s->top;
    s->top = new;
}

string stack_pop(stack s) {
    assert(s != NULL);
    Node *out = s->top;
    s->top = s->top->next;
    return out->data;
}

string stack_peek(stack s) {
    return s->top->data;
}

bool stack_empty(stack s) {
    if (!s->top) {
        return true;
    } else {
        return false;
    }
}
