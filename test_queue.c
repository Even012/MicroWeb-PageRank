#include <stdio.h>
#include "queue.h"
#include "assert.h"
#include "string.h"

int main(void) {
    
    string s1 = "string 1";
    string s2 = "string 2";
    string line;

    queue q = queue_create();
    assert(queue_empty(q));

    queue_enqueue(q, s1);
    assert(!queue_empty(q));

    queue_enqueue(q, s2);
    assert(!queue_empty(q));

    while (!queue_empty(q)) {
        line = queue_peek(q);
        printf("Peek: %s\t", line);
        line = queue_dequeue(q);
        printf("Dequeue: %s\t", line);
        printf("Empty: %s\n", queue_empty(q) ? "Yes" : "No");
        
    }
    // string s3 = queue_peek(q);
    // assert(!strcmp(s3, s1));

    // s3 = queue_dequeue(q);
    // assert(!strcmp(s3, s1));
    // assert(!queue_empty(q));

    // s3 = queue_dequeue(q);
    // assert(!strcmp(s3, s2));
    // assert(queue_empty(q));

    printf("all tests passesd.\n");
    queue_destroy(q);

    return 0;
}

/**
 * Crude driver program to test queue ADT for COMP9024 Pagerank Assignment
 *
 * Written by: Tim Arney <t.arney@unsw.edu.au>
 * Date: 17/07/2022
 *
 */

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/types.h>

// #include "queue.h"

// int main(void) {
//     string line = NULL;
//     size_t len = 0;
//     ssize_t read;

//     queue q = queue_create();
//     printf("Empty: %s\n", queue_empty(q) ? "Yes" : "No");

//     while ((read = getline(&line, &len, stdin)) != -1) {
//         queue_enqueue(q, line);
//         printf("Enqueue: %s", line);
//         printf("Empty: %s\n", queue_empty(q) ? "Yes" : "No");
//         // free(line);
//         line = NULL;
//     }

//     // free(line);

//     if (ferror(stdin)) {
//         return EXIT_FAILURE;
//     }

//     while (!queue_empty(q)) {
//         line = queue_peek(q);
//         printf("Peek: %s", line);
//         line = queue_dequeue(q);
//         printf("Dequeue: %s", line);
//         printf("Empty: %s\n", queue_empty(q) ? "Yes" : "No");
//         free(line);
//     }

//     queue_destroy(q);

//     return EXIT_SUCCESS;
// }
