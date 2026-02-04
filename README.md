# Memory-Allocator
A manual memory management implementation built from scratch in C++. This project replaces standard new/delete calls with a custom pool allocator using a Doubly Linked Free List with First-Fit allocation strategy.

## Features

- Memory Pool Allocation: Pre-allocates a large continuous block of memory in order to minimise syscalls.
- Coalescing: Automatically merges adjacent free blocks upon deallocation to prevent fragmentation.
- Block Splitting: efficient use of memory by splitting large free blocks into the exact size required.
- Doubly Linked List: optimized `O(1)` removal of memory blocks during allocation.

## Code example

```cpp
// Request 1000 bytes of raw memory and pass it into the allocator
char* memoryPool = new char[1000];
cAlloc* allocator = new cAlloc(memoryPool, 1000);

// Allocation of memory
int* ptr1 = static_cast<int*>(allocator->alloc(sizeof(int)));
*ptr1 = 10;

// Deallocation of memory
allocator->dealloc(static_cast<void*>(ptr1));
```

