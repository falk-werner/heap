// SPDX-Licence-Identifier: MIT
// Copyright Falk Werner <github.com/falk-werner>

#ifndef HEAP_H
#define HEAP_H

#ifndef __cplusplus
#include <stddef.h>
#else
#include <cstddef>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/// \brief Defines a heap node.
struct heap_node
{
    size_t id;  ///< id of node in heap; changes due to heap operations
};

/// \brief Compares two heap nodes.
///
/// \param node  node to compare
/// \param other node to comapre
/// \return 0  if value of \arg node is equal to value of \arg other
///         >0 if value of \arg node is greater than value of \arg other
///         <0 if value of \arg node is less to value of \arg other
typedef int
heap_compare_fn(
    struct heap_node * node,
    struct heap_node * other);

/// \brief Defines a heap.
struct heap
{
    struct heap_node * * data;  ///< references to heap nodes
    size_t size;                ///< count of nodes in the heap
    size_t capacity;            ///< capacity of the heap; will be increased if necessary
    heap_compare_fn * compare;  ///< compare function used for heap nodes
};

/// \brief Initialized a heap.
///
/// \param self    pointer to heap to initialize
/// \param compare compare function used for heap nodes
extern void
heap_init(
    struct heap * self,
    heap_compare_fn * compare);

/// \brief Cleans up a heap.
extern void
heap_cleanup(
    struct heap * self);

/// \brief Returns a pointer of the top node without removing it.
///
/// \param self pointer to the heap
/// \return pointer to the top node or NULL if heap is empty
extern struct heap_node *
heap_peek(
    struct heap * self);

/// \brief Adds a new node to the heap.
///
/// \param self pointer to the heap
/// \param node node to add
extern void
heap_add(
    struct heap * self,
    struct heap_node * node);

/// \brief Removes the top node of the heap.
///
/// \param self pointer to the heap
/// \return pointer to the former top node or NULL if heap is empty
extern struct heap_node *
heap_extract(
    struct heap * self);

/// \brief Remodes a node from the heap.
///
/// \param self pointer to the heap
/// \param node node to remove
extern void
heap_remove(
    struct heap * self,
    struct heap_node * node);

#ifdef __cplusplus
}
#endif

#endif
