 
#ifndef __MATIDIGO__SYSCALLS_H
#define __MATIDIGO__SYSCALLS_H

#include "types.h"
#include "hardware/interrupts.h"
#include "multitasking.h"

namespace matidigo
{
    
    class SyscallHandler : public hardware::InterruptHandler
    {
        
    public:
        SyscallHandler(hardware::InterruptManager* interruptManager, matidigo::types::uint8_t InterruptNumber);
        ~SyscallHandler();
        
        virtual matidigo::types::uint32_t HandleInterrupt(matidigo::types::uint32_t esp);

    };
    
    
}


#endif