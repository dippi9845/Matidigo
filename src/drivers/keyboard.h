#ifndef __MATIDIGO__DRIVERS__KEYBOARD_H
#define __MATIDIGO__DRIVERS__KEYBOARD_H

#include "driver.h"

#include "../types.h"

#include "../hardware/interrupts.h"
#include  "../hardware/port.h"

namespace matidigo
{
    namespace drivers
    {
    
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
        class KeyboardDriver : public matidigo::hardware::InterruptHandler, public Driver
        {
            matidigo::hardware::Port8Bit dataport;
            matidigo::hardware::Port8Bit commandport;
            
            KeyboardEventHandler* handler;
        public:
            KeyboardDriver(matidigo::hardware::InterruptManager* manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual matidigo::types::uint32_t HandleInterrupt(matidigo::types::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif