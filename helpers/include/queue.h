#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#include <result.h>

struct list_node {
    struct list_node *next;
    size_t data;
};

struct queue {
    struct list_node *head;
    struct list_node *tail;
};

struct queue queue_ctor();
void queue_dtor(struct queue *q);

bool queue_is_empty(struct queue *q);

struct result queue_push(struct queue *q, size_t data);
struct result queue_pop(struct queue *q);

#endif //QUEUE_H
