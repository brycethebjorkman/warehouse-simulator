// utilities needed by multiple reactors

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define MIN_PALLETQUEUE_SIZE 1
#define MAX_PALLETQUEUE_SIZE 52

typedef struct Input {
    uintmax_t   time;
    uintmax_t   gate;
    uintmax_t   pallets[MAX_PALLETQUEUE_SIZE];
    size_t      num_pallets;
} Input;

typedef struct InputNode {
    struct Input            input;
    SLIST_ENTRY(InputNode)  next;
} InputNode;

typedef struct InputQueue {
    SLIST_HEAD(InputHead, InputNode) head;
} InputQueue;

int parse_input_csv(const char* filename, InputQueue* out);

#endif
