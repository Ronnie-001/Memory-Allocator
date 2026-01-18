#include "cAlloc.h"
#include "memBlock.h"

int main()
{
    char* rawMemory = new char[1000];
    cAlloc* allocator = new cAlloc(rawMemory, sizeof(rawMemory));

    delete allocator;
    delete[] rawMemory;

    return 0;
}
