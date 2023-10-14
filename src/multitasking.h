#ifndef __MATIDIGO__MULTITASKING_H
#define __MATIDIGO__MULTITASKING_H

#define MAX_TASKS 256
#define STACK_ELEMENTS 0x1000


#include "types.h"
#include "global_descriptor_table.h"

namespace matidigo
{
    
    struct CPUState
    {
        types::uint32_t eax;
        types::uint32_t ebx;
        types::uint32_t ecx;
        types::uint32_t edx;

        types::uint32_t esi;
        types::uint32_t edi;
        types::uint32_t ebp;

        types::uint32_t error;

        types::uint32_t eip;
        types::uint32_t cs;
        types::uint32_t eflags;
        types::uint32_t esp;
        types::uint32_t ss;        
    } __attribute__((packed));
    
    
    class Task {
    
        friend class TaskManager;
        
        private:
            types::uint8_t stack[STACK_ELEMENTS]; // 4 KiB
            CPUState* cpustate;
        public:
            Task(GlobalDescriptorTable *gdt, void entrypoint());
            ~Task();
    };
    
    
    class TaskManager {
        private:
            Task* tasks[MAX_TASKS];
            int numTasks;
            int currentTask;
        public:
            TaskManager();
            ~TaskManager();
            bool AddTask(Task* task);
            CPUState* Schedule(CPUState* cpustate);
    };
    
    
    
}


#endif