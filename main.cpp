#include "cAlloc.h"
#include "memBlock.h"

int main()
{
    char* rawMemory = new char[100];
    cAlloc* allocator = new cAlloc(rawMemory, 100);
    
    // Allocate memory
    int* ptr1 = static_cast<int*>(allocator->alloc(sizeof(int)));
    *ptr1 = 42;

    // Deallcate memory

    
    delete allocator;
    delete[] rawMemory;

    return 0;
}
