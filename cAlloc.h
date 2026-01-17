#ifndef CALLOC_H
#define CALLOC_H

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <type_traits>
#include "memBlock.h"

// The class that will be used for the allocator.
class cAlloc
{
// member variable(s)
private:
    char* m_memPool;
    std::size_t m_size;
    // Used to keep reference to the head of the "free list" (Linked List)
    memBlock* m_header;

public:
    // constructor
    cAlloc(char* memPool, std::size_t size) 
    : m_memPool(memPool),
      m_size(size)
    {
        m_header = new memBlock;
        buildFreeList(m_header, m_memPool, m_size);
    }
    
    // destructor
    ~cAlloc() {}

    cAlloc(const cAlloc& calloc) = delete;

    template<typename T> 
    void alloc(std::size_t size) 
    {
        // Scan through the free list and find an avalible memory spot
        memBlock* curr = new memBlock;
        curr = m_header;

        std::size_t total = 0;
        std::size_t i = 0;
        void* ptr;
        
        while (curr != nullptr) {
            // Check if the memory requested has been found in the memory pool.
            if (total == size) break;  
            // Keep track of the first memory block.
            if (i == 0) { ptr = curr->ptr; }

            total += curr->size;
            i++;

            // Move onto the next memory block
            curr = curr->next;
        }
        
        // check if the total was not reached.
        if (total != size) {
            std::cout << "Not enough memory within the memory pool to allocate" << '\n';  
        } else {
            // Starting at void* ptr, go through and delete the memory blocks, from the free list
            // since they have been allocated already
        }

        delete curr;
    }

    void dealloc(void* ptr) {} 

private:
    /* Function used to construct the free list. 
      Returns a memBlock* to the head of the constructed free list.
    */
    void buildFreeList(memBlock* head, char* memPool, const std::size_t size)
    {
        memBlock* temp; 
        for (std::size_t i = 0; i < size; i+= 4) {
            if (i == 0) {
                head->ptr = static_cast<void*>(memPool);
                head->prev = nullptr;
                head->next = nullptr;
                head->size = 4;
                
                std::cout << "HEAD: " << head->ptr << '\n';

                temp = head; 
            } else {
                memBlock* newBlock = new memBlock;                
                // Set metadata about the block.
                newBlock->ptr = static_cast<void*>(&memPool[i]);
                newBlock->next = nullptr;  
                newBlock->prev = temp; 
                newBlock->size = 4; // represents 4 bytes
                
                // Move forward.
                temp->next = newBlock;
                temp = newBlock;

                std::cout << "[" << &newBlock << "]" << ":" << "[" << newBlock->prev << "]" << "->";
            }
        }
    }
    
    // Function used to remove block from LL once all
    // the memory from that block has been allocated.
    void removeMemoryBlock(memBlock* block)
    {
        // take the next block of memory
        memBlock* nextMemBlock = block->prev;
        memBlock* prevMemBlock = block->prev;
        
        prevMemBlock->next = nextMemBlock;
        
        // Deallocate memory accociated with the block.
        delete block;
    }

    // Mainly used in the case coalasing of memory has to happen.
    void addMemoryBlock(std::size_t size, memBlock* prev) 
    {
        memBlock* newBlock = new memBlock;

        // Cast the pointer to char* so we can be more specific 
        // About the amount of memory we want to add.
        char* charPtr = static_cast<char*>(prev->ptr);
        charPtr += size;

        newBlock->size = size;
    }
};


#endif // !CALLOC_H
#define CALLOC_H
