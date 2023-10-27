
#ifndef __MATIDIGO__DRIVERS__MOUSE_H
#define __MATIDIGO__DRIVERS__MOUSE_H

#include "driver.h"

#include "../types.h"
#include "../hardware/port.h"
#include "../hardware/interrupts.h"

namespace matidigo
{
    namespace drivers
    {
    
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(matidigo::types::uint8_t button);
            virtual void OnMouseUp(matidigo::types::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };
        
        
        class MouseDriver : public matidigo::hardware::InterruptHandler, public Driver
        {
            matidigo::hardware::Port8Bit dataport;
            matidigo::hardware::Port8Bit commandport;
            matidigo::types::uint8_t buffer[3];
            matidigo::types::uint8_t offset;
            matidigo::types::uint8_t buttons;

            MouseEventHandler* handler;
        public:
            MouseDriver(matidigo::hardware::InterruptManager* manager, MouseEventHandler* handler);
            ~MouseDriver();
            virtual matidigo::types::uint32_t HandleInterrupt(matidigo::types::uint32_t esp);
            virtual void Activate();
        };

    }
}
    
#endif
