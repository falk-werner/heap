#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type,member) );})

struct node
{
    struct heap_node heap_node;
    int value;
};

static int
compare(
    struct heap_node * node,
    struct heap_node * other)
{
    struct node * a = container_of(node , struct node, heap_node);
    struct node * b = container_of(other, struct node, heap_node);

    return a->value - b->value;
}

static void
dump_heap(
    struct heap * heap)
{
    printf("heap: size=%zu, values=", heap->size);
    for (size_t i = 0; i < heap->size; i ++)
    {
        struct heap_node * heap_node = heap->data[i];
        struct node * node = container_of(heap_node, struct node, heap_node);
        printf("%d ", node->value);
    }
    printf("\n");
}


int main(int argc, char * argv[])
{
    if (argc <= 1)
    {
        printf("usage: min-heap [<value> ...]\n");
        exit(EXIT_SUCCESS);
    }


    struct heap heap;
    heap_init(&heap, &compare);
    struct node * nodes = malloc(sizeof(struct node) * argc);

    printf("insert\n");
    for (size_t i = 1; i < argc; i++)
    {
        struct node * node = &nodes[i];
        node->value = atoi(argv[i]);

        printf("insert %d\n", node->value);
        heap_add(&heap, &node->heap_node);
        dump_heap(&heap);
    }

    printf("\nremove\n");
    while (heap.size > 0)
    {
        struct heap_node * heap_node = heap_extract(&heap);
        struct node * node = container_of(heap_node, struct node, heap_node);
        printf("%d\n", node->value);
        dump_heap(&heap);
    }

    printf("\ninsert again\n");
    for (size_t i = 1; i < argc; i++)
    {
        struct node * node = &nodes[i];
        printf("insert %d\n", node->value);
        heap_add(&heap, &node->heap_node);
        dump_heap(&heap);
    }

    printf("\nremove by id\n");
    for(size_t i = 1; i < argc; i++)
    {
        size_t id = argc - i;
        struct node * node = &nodes[id];
        printf("remove #%zu: value = %d\n", id, node->value);
        heap_remove(&heap, &node->heap_node);
        dump_heap(&heap);
    }


    free(nodes);
    heap_cleanup(&heap);
    return EXIT_SUCCESS;
}
