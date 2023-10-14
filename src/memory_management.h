#ifndef __MATIDIGO__MEMORYMANAGEMENT_H
#define __MATIDIGO__MEMORYMANAGEMENT_H

#include "types.h"


namespace matidigo
{
    
    struct MemoryChunk
    {
        MemoryChunk *next;
        MemoryChunk *prev;
        bool allocated;
        types::size_t size;
    };
    
    
    class MemoryManager
    {
        
    protected:
        MemoryChunk* first;
    public:
        
        static MemoryManager *activeMemoryManager;
        
        MemoryManager(types::size_t first, types::size_t size);
        ~MemoryManager();
        
        void* malloc(types::size_t size);
        void free(void* ptr);
    };
}


void* operator new(unsigned int size);
void* operator new[](unsigned int size);


void* operator new(matidigo::types::size_t size, void* ptr);
void* operator new[](matidigo::types::size_t size, void* ptr);

void operator delete(void* ptr);
void operator delete[](void* ptr);


#endif