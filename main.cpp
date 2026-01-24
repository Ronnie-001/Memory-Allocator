#include "cAlloc.h"
#include "memBlock.h"

int main()
{
    char* rawMemory = new char[100];
    cAlloc* allocator = new cAlloc(rawMemory, 100);
    
    int* ptr = static_cast<int*>(allocator->alloc(sizeof(int)));
    *ptr = 42;

    delete allocator;
    delete[] rawMemory;

    return 0;
}
