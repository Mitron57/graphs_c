#include <queue.h>

struct queue queue_ctor() {
    return (struct queue){NULL, NULL};
}

void queue_dtor(struct queue *q) {
    if (q->head != NULL) {
        while (q->head != NULL) {
            struct list_node *next = q->head->next;
            free(q->head);
            q->head = next;
        }
    }
}

bool queue_is_empty(struct queue *q) {
    return q->head == NULL;
}

struct result queue_push(struct queue *q, size_t data) {
    struct list_node *next = malloc(sizeof(struct list_node));
    if (next == NULL) {
        return err("Could not allocate memory");
    }

    next->data = data;
    next->next = NULL;

    if (q->head == NULL) {
        q->head = next;
        q->tail = next;
        return ok(data);
    }

    q->tail->next = next;
    q->tail = next;

    return ok(data);
}

struct result queue_pop(struct queue *q) {
    if (q->head == NULL) {
        return err("Queue is empty");
    }
    struct list_node *head = q->head;
    q->head = head->next;
    const size_t data = head->data;
    free(head);
    return ok(data);
}