// SPDX-Licence-Identifier: MIT
// Copyright Falk Werner <github.com/falk-werner>

#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>

#define HEAP_INITIAL_CAPACITY 16

static size_t
heap_left(size_t id)
{
    return (2 * id) + 1;
}

static size_t
heap_right(size_t id)
{
    return (2 * id) + 2;
}

static size_t
heap_parent(size_t id)
{
    return (id - 1) / 2;
}

static void
heap_swap(
    struct heap * self,
    int id,
    int id_other)
{
    struct heap_node * temp;

    temp = self->data[id];
    self->data[id] = self->data[id_other];
    self->data[id_other] = temp;

    self->data[id]->id = id;
    self->data[id_other]->id = id_other;
}

static void
heap_sink(
    struct heap * self,
    size_t id)
{
    size_t actual = id;
    bool finished = false;

    while (!finished)
    {
        size_t min = actual;

        size_t left = heap_left(actual);
        if ((left < self->size) && (0 > self->compare(self->data[left], self->data[min])))
        {
            min = left; 
        }

        size_t right = heap_right(actual);
        if ((right < self->size) && (0 > self->compare(self->data[right], self->data[min])))
        {
            min = right;
        }

        if (actual == min)
        {
            finished = true;
        }
        else
        {
            heap_swap(self, actual, min);
            actual = min;
        }
    } 
}

static void
heap_rise(
    struct heap * self,
    int id)
{
    size_t parent = heap_parent(id);
    while ((id > 0) && (0 > self->compare(self->data[id], self->data[parent])))
    {
        heap_swap(self, id, parent);
        id = parent;
        parent = heap_parent(id);
    }
}


void
heap_init(
    struct heap * self,
    heap_compare_fn * compare)
{
    self->data = malloc(sizeof(struct heap_node *) * HEAP_INITIAL_CAPACITY);
    self->size = 0;
    self->capacity = HEAP_INITIAL_CAPACITY;
    self->compare = compare;
}

void
heap_cleanup(
    struct heap * self)
{
    free(self->data);
    self->data = NULL;
    self->size = 0;
    self->capacity = 0;
    self->compare = NULL;
}

struct heap_node *
heap_peek(
    struct heap * self)
{
    struct heap_node * result = NULL;

    if (self->size > 0)
    {
        result = self->data[0];
    }

    return result;
}

void
heap_add(
    struct heap * self,
    struct heap_node * node)
{
    if (self->size == self->capacity)
    {
        self->capacity *= 2;
        self->data = realloc(self->data, sizeof(struct heap_node *) * self->capacity);
    }

    size_t last = self->size;
    self->size++;
    self->data[last] = node;
    node->id = last;

    heap_rise(self, last);
}

struct heap_node *
heap_extract(
    struct heap * self)
{
    struct heap_node * result = NULL;
    if (self->size > 0)
    {
        result = self->data[0];
        self->size--;
        heap_swap(self, 0, self->size);
        heap_sink(self, 0);
    }

    return result;
}

void
heap_remove(
    struct heap * self,
    struct heap_node * node)
{
    size_t id = node->id;

    if (id < self->size)
    {
        int last = self->size -1;
        heap_swap(self, id, last);
        self->size--;

        if (id != last)
        {
            size_t parent = heap_parent(id);
            if ((id == 0) || (0 > self->compare(self->data[id], self->data[parent])))
            {
                heap_sink(self, id);
            }
            else
            {
                heap_rise(self, id);
            }
        }
    }
}
