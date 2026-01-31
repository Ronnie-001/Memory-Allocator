#ifndef CALLOC_H
#define CALLOC_H

#include <cstddef>
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
    
    // Delete the copy constructor to avoid copies of the memory pool being cosntructed.
    cAlloc(const cAlloc& calloc) = delete;

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
                if (curr->size > requestedMemory) {
                    // Split the memory block.
                    splitMemoryBlock(curr, requestedMemory);
                    std::cout << '\n';
                    std::cout << "new free list:" << '\n';
                    printFreeList();
                }
                           
                // Return the pointer to the block of memory.
                return curr->ptr;
            }

            curr = curr->next;
        }
            
        // ONLY if the requested memory cannot be allocated.
        return nullptr;
    }

    void dealloc(void* ptr)
    {
        // Loop through the free list to find the matching memory address
        memBlock* curr = m_header;

        while (curr != nullptr) {
            if (ptr == curr->ptr) {
                // Mark the avaliable block as free to use.
                curr->isAllocated = false;   
                break; 
            }
            curr = curr->next;
        } 

       printFreeList();
    } 

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

                head->prev = nullptr;
                head->next = nullptr;
                
                // For debug purposes.
                std::cout << "HEAD: " << head->ptr << '\n';
                temp = head; 
                
            } else {
                memBlock* newBlock = new memBlock;                
                // Set metadata about the block.
                newBlock->ptr = static_cast<void*>(&memPool[i]);
                newBlock->size = 20; // represents 20 bytes

                newBlock->next = nullptr;  
                newBlock->prev = temp; 
                
                // Move forward.
                temp->next = newBlock;
                temp = newBlock;
                
                // For debug purposes.
                std::cout << "[" << newBlock->ptr << "]" << ":" << newBlock->size << ":" << "[" << newBlock->prev->ptr << "]" << "->";
            }
        }
    }

    /* Function used for splitting memory blocks if the request amount of memory 
     * is less than the size of the memory block allocated.
     */
    void splitMemoryBlock(memBlock* block, std::size_t newBlockSize)
    {
        std::size_t newSize = (block->size) - newBlockSize;

        block->size = newBlockSize;
        block->isAllocated = true;

        memBlock* newBlk = createMemoryBlock(newSize, block, block->next);

        void* blkPtr = block->ptr;           

        // Cast to char* so the pointer can be incremented by x bytes.
        char* charPtr = static_cast<char*>(blkPtr);
        charPtr += newBlockSize;
        newBlk->ptr = static_cast<void*>(charPtr);

        // point torwards the new block
        block->next = newBlk;
    } 

    /* 
     * Function used to remove block from LL once all
     the memory from that block has been allocated.
    */
    void removeMemoryBlock(memBlock* block)
    {
        // take the next block of memory
        memBlock* nextMemBlock = block->prev;
        memBlock* prevMemBlock = block->prev;
        
        prevMemBlock->next = nextMemBlock;
        
        // Deallocate memory accociated with the block.
        delete block;
    }
    
    /* 
     * Function used to create a new memBlock in the free list in the 
     * case where the total amount of requested memory is less than thes size of 
     * the memory block. 
     *
     * Initalises the size, prev and next member variables of the struct.
    */
    memBlock* createMemoryBlock(std::size_t size, memBlock* prev, memBlock* next) 
    {
        memBlock* newBlock = new memBlock;

        newBlock->size = size;
        newBlock->prev = prev;
        newBlock->next = next;

        return newBlock;
    }
    
    /* 
     * Function used to print out the free list.
     * Written mainly for debugging purposes.
    */
    void printFreeList() 
    {
        memBlock* curr = m_header;

        while (curr != nullptr) {
            if (curr->isAllocated) {
                if (curr->prev == nullptr) {
                    std::cout << "(A)" << "[" << curr->ptr << "]" << ":" << curr->size << "->"; 
                } else {
                    std::cout << "(A)" << "[" << curr->ptr << "]" << ":" << curr->size << ":" << "[" << curr->prev->ptr << "]" << "->"; 
                }
            } else {
                if (curr->prev == nullptr) {
                    std::cout << "[" << curr->ptr << "]" << ":" << curr->size << ":" << "->"; 
                } else {
                    std::cout << "[" << curr->ptr << "]" << ":" << curr->size << ":" << "[" << curr->prev->ptr << "]" << "->"; 
                }
            }
            curr = curr->next;
        }
    }
};

#endif // !CALLOC_H
#define CALLOC_H
