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

    // TODO: Fix alloc() implementation to allocate one *contiguous* block of memory.
    // Function used to alloc
    template<typename T> 
    void* alloc(std::size_t requestedMemory) 
    {
        memBlock* curr; 
        curr = m_header;

        // Search the free list for an avaliable memory loation.
        while (curr != nullptr) {
            if (curr->isAllocated) {
                curr = curr->next;
                continue;
            }

            if (curr->size >= requestedMemory) {
                T* ptr = static_cast<T*>(curr->ptr); 
                // Allocate memory acording to the size of the DS passed in.
                ptr += sizeof(T);
                curr->isAllocated = true;
                
                return curr->ptr;
            }
            curr = curr->next;
        }
            
        // ONLY if the requested memory cannot be allocated.
        return nullptr;
    }

    void dealloc(void* ptr) {} 

private:
    /* Function used to construct the free list. 
      Returns a memBlock* to the head of the constructed free list.
    */
    void buildFreeList(memBlock* head, char* memPool, const std::size_t size)
    {
        memBlock* temp; 
        for (std::size_t i = 0; i < size; i+= 20) {
            if (i == 0) {
                head->ptr = static_cast<void*>(memPool);
                head->size = 20;
                head->isAllocated = false;

                head->prev = nullptr;
                head->next = nullptr;
                
                std::cout << "HEAD: " << head->ptr << '\n';

                temp = head; 
            } else {
                memBlock* newBlock = new memBlock;                
                // Set metadata about the block.
                newBlock->ptr = static_cast<void*>(&memPool[i]);
                newBlock->size = 20; // represents 20 bytes
                newBlock->isAllocated = false;


                newBlock->next = nullptr;  
                newBlock->prev = temp; 
                
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
