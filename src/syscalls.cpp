
#include "syscalls.h"
 
using namespace matidigo;
using namespace matidigo::types;
using namespace matidigo::hardware;
 
SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t InterruptNumber)
:    InterruptHandler(interruptManager, InterruptNumber  + interruptManager->HardwareInterruptOffset())
{
}

SyscallHandler::~SyscallHandler()
{
}


void printf(char*);

uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState* cpu = (CPUState*)esp;
    

    switch(cpu->eax)
    {
        case 4:
            printf((char*)cpu->ebx);
            break;
            
        default:
            break;
    }

    
    return esp;
}

