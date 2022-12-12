#include <stdio.h>
#include <stdlib.h>

#include "pq.h"
#include "node.h"

struct PriorityQueue {
    int32_t capacity;
    int32_t top;
    Node **queue;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->queue = (Node **) calloc(capacity, sizeof(Node));
        q->capacity = capacity;
        q->top = 0;
        if (!q->queue) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->queue) {
        free((*q)->queue);
        free(*q);
        *q = NULL;
    }
}

bool pq_empty(PriorityQueue *q) {
    if (q->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool pq_full(PriorityQueue *q) {
    if (q->top >= q->capacity) {
        return true;
    } else {
        return false;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    return (uint32_t) q->top;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }

    if (pq_size(q) == 0) {
        q->queue[0] = n;
        q->top += 1;
        return true;

    } else {
        for (int32_t i = 0; i < q->top; i += 1) {
            if (n->frequency < (q->queue[i])->frequency) {
                for (int32_t j = (q->top - 1); j > (i - 1); j -= 1) {
                    q->queue[j + 1] = q->queue[j];
                }
                q->queue[i] = n;
                q->top += 1;
                return true;
            }
	    else if(n->frequency == (q->queue[i])->frequency)
	    {
		for (int32_t j = (q->top - 1); j > i; j -=1)
		{
			q->queue[j + 1] = q->queue[j];
		}
		q->queue[i + 1] = n;
		q->top += 1;
		return true;
	    }
        }
	if(n->frequency > (q->queue[q->top-1])->frequency)
	{
		q->queue[q->top] = n;
		q->top ++;
		return true;
	}
    }
    return false;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }

    *n = q->queue[0];
    q->top -= 1;
    for(int32_t i = 0; i < q->top; i++)
    {
	q->queue[i] = q->queue[i+1];
    }
    return true;
}

void pq_print(PriorityQueue *q) {
    for (uint32_t k = 0; k < pq_size(q); k += 1) {
        node_print(q->queue[k]);
        printf("\n");
    }
}
