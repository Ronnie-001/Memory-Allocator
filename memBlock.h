#ifndef MEMBLOCK_H
#define MEMBLOCK_H

// Used to keep track of avaliable memory spaces within the free list
struct memBlock 
{
    // include metadata.
    void* ptr;
    memBlock* next;
    memBlock* prev;
    int size;
};

#endif // !MEMBLOCK_H
#define MEMBLOCK_H
