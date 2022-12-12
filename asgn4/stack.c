#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//stack struct, stack create, stack delete, and stack print were all from assignment pdf

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

//create stack struct by allocating both stack and array, or none at all
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//free stack and array
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
}

//return the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

//return whether the stack is empty or not
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

//return whether the stack is full or not
bool stack_full(Stack *s) {
    if (s->top >= s->capacity) {
        return true;
    } else {
        return false;
    }
}

//push and item onto the stack and return whether there was a successful attempt at pushing an item to the stack
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = x;
        s->top += 1;
        return true;
    }
}

//pop the top item from the stack and return whether it was successful
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[s->top - 1];
        s->items[s->top - 1] = 0;
        s->top -= 1;
        return true;
    }
}

//put the top item in the stack into x and return if it was successful
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[s->top - 1];
        return true;
    }
}

//copy stack from src to dst
void stack_copy(Stack *dst, Stack *src) {
    dst->top = src->top;

    for (uint32_t i = 0; i < dst->top; i += 1) {
        dst->items[i] = src->items[i];
    }
}

//print stack in a specific way to outfile
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path: ");
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
