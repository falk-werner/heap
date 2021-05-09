# Heap Implementation in C

This project contains a simple heap implementation in C.

A heap is a data structure used to store partially ordered elements. It provides fast access to the top-most elment, the element with the lowest (or highest) value. Therefore, heaps are usually used to implement prioritized queues.

This implementation stores the actual heap nodes outside of the heap an keeps track of their position within the heap. So one can easily remove random elements from the heap.

If you don't need to remove random elements from the heap, you may consider some other implementation.

## Build

````
meson build
cd build
meson compile
sudo meson install
````

## Runtime Complexity

| Operation | Description                           | Complexity |
| --------- |---------------------------------------|:----------:|
| peek      | get top element without removing it   | O(1)       |
| add       | add a new element to the heap         | O(log n)   |
| extract   | remove top element from the heap      | O(log n)   |
| remove    | remove a random element from the heap | O(log n)   |
