#include "cAlloc.h"
#include "memBlock.h"

int main()
{
    char* rawMemory = new char[100];
    cAlloc* allocator = new cAlloc(rawMemory, 100);

    std::cout << "\n";
    std::cout << "Allocate Memory" << "\n";

    // Allocate memory
    int* ptr1 = static_cast<int*>(allocator->alloc(sizeof(int)));
    *ptr1 = 42;

    std::cout << "\n";
    std::cout << "Deallocate Memory" << "\n";

    allocator->dealloc(static_cast<void*>(ptr1));

    delete allocator;
    delete[] rawMemory;

    return 0;
}
