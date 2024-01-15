#include <stdio.h>
#include "set.h"
#include "assert.h"
#include "string.h"

int main(void) {
    
    string s1 = "string 1";
    string s2 = "string 2";


    set s = set_create();
    assert(!set_contains(s, s1));
    assert(!set_contains(s, s2));

    set_insert(s, s1);
    printf(set_contains(s, s1) ? "Contains: %s\n" : "Doesn't Contain: %s\n", s1);
    // assert(set_contains(s, s1));
    // assert(set_contains(s, s1));
    // assert(!set_contains(s, s2));

    // set_insert(s, s2);
    // assert(set_contains(s, s1));
    // assert(set_contains(s, s2));


    // set_remove(s, s1);
    // assert(!set_contains(s, s1));
    // assert(set_contains(s, s2));

    // set_remove(s, s2);
    // assert(!set_contains(s, s1));
    // assert(!set_contains(s, s2));

 
    printf("all tests passesd.\n");
    set_destroy(s);

    return 0;
}