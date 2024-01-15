#include <stdio.h>
#include "pqueue.h"
#include "assert.h"
#include "string.h"

int main(void) {
    
    string s1 = "string 1";
    string s2 = "string 2";
    string s3 = "string 3";
    


    pqueue pq = pqueue_create();
    assert(pqueue_empty(pq));

    pqueue_join(pq, s1, 0.2);
    assert(!pqueue_empty(pq));

    pqueue_join(pq, s2, 0.1);
    assert(!pqueue_empty(pq));

    pqueue_join(pq, s3, 0.4);
    assert(!pqueue_empty(pq));

    string s4 = pqueue_peek(pq);
    assert(!strcmp(s4, s2));

    s4 = pqueue_leave(pq);
    assert(!strcmp(s4, s2));
    assert(!pqueue_empty(pq));

    s4 = pqueue_leave(pq);
    assert(!strcmp(s4, s1));
    assert(!pqueue_empty(pq));

    s4 = pqueue_leave(pq);
    assert(!strcmp(s4, s3));
    assert(pqueue_empty(pq));

    printf("all tests passesd.\n");
    pqueue_destroy(pq);

    return 0;
}