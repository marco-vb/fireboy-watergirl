#include "queue.h"
#include <stddef.h>
#include <stdlib.h>

struct Queue_val{
    uint8_t val;
    Queue_val *next;
};

struct Queue {
    Queue_val *front;
    Queue_val *back;
};

Queue* create_queue() {
    Queue *q = malloc(sizeof(Queue));

    q->front = NULL;
    q->back = NULL;

    return q;
}

void destroy_queue(Queue *q) {
    clear_queue(q);

    free(q);
}

void push(Queue *q, uint8_t val) {
    Queue_val *q_val = malloc(sizeof(Queue_val));
    q_val->val = val;
    q_val->next = NULL;

    if (is_empty(q)) {
        q->front = q->back = q_val;
    }
    else {
        q->back->next = q_val;
        q->back = q->back->next;
    }
}

void pop(Queue *q) {
    if (is_empty(q))
        return;
    
    Queue_val *tmp = q->front;
    q->front = q->front->next;

    free(tmp);
}

uint8_t front(Queue *q) {
    return q->front->val;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void clear_queue(Queue *q) {
    while (!is_empty(q)) {
        pop(q);
    }
}
