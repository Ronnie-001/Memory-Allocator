#include "cAlloc.h"
#include "memBlock.h"

int main()
{
    char* rawMemory = new char[24];
    cAlloc* allocator = new cAlloc(rawMemory, 24);

    delete allocator;
    delete[] rawMemory;

    return 0;
}
