#include <stdio.h>
#include "stack.h"
#include "assert.h"
#include "string.h"

int main(void) {
    
    string s1 = "string 1";
    string s2 = "string 2";


    stack s = stack_create();
    assert(stack_empty(s));

    stack_push(s, s1);
    assert(!stack_empty(s));

    stack_push(s, s2);
    assert(!stack_empty(s));


    string s3 = stack_peek(s);
    assert(!strcmp(s3, s2));

    s3 = stack_pop(s);
    assert(!strcmp(s3, s2));
    assert(!stack_empty(s));

    s3 = stack_pop(s);
    assert(!strcmp(s3, s1));
    assert(stack_empty(s));

    printf("all tests passesd.\n");
    stack_destroy(s);

    return 0;
}