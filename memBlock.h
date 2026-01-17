#ifndef MEMBLOCK_H
#define MEMBLOCK_H

// Used to keep track of avaliable memory spaces within the free list
#include <cstddef>
struct memBlock 
{
    // include metadata.
    void* ptr;
    memBlock* next;
    memBlock* prev;
    std::size_t size;
};

#endif // !MEMBLOCK_H
#define MEMBLOCK_H
