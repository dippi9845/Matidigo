 
#ifndef __MATIDIGO__DRIVERS__ATA_H
#define __MATIDIGO__DRIVERS__ATA_H

#include "../types.h"
#include "../hardware/interrupts.h"
#include "../hardware/port.h"

namespace matidigo
{
    namespace drivers
    {
        
        class AdvancedTechnologyAttachment
        {
        protected:
            bool master;
            hardware::Port16Bit dataPort;
            hardware::Port8Bit errorPort;
            hardware::Port8Bit sectorCountPort;
            hardware::Port8Bit lbaLowPort;
            hardware::Port8Bit lbaMidPort;
            hardware::Port8Bit lbaHiPort;
            hardware::Port8Bit devicePort;
            hardware::Port8Bit commandPort;
            hardware::Port8Bit controlPort;
        public:
            
            AdvancedTechnologyAttachment(bool master, types::uint16_t portBase);
            ~AdvancedTechnologyAttachment();
            
            void Identify();
            void Read28(types::uint32_t sectorNum, int count = 512);
            void Write28(types::uint32_t sectorNum, types::uint8_t* data, types::uint32_t count);
            void Flush();
            
            
        };
        
    }
}

#endif
