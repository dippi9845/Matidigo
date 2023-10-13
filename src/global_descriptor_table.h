#ifndef GLOBAL_DESCRIPTOR_TABLE_H
#define GLOBAL_DESCRIPTOR_TABLE_H

#define MAX_ADDRESSABLE_16BIT_MEMORY 0x10000
#define FIRST_12_ONES 0xFFF

#include "types.h"

namespace matidigo {
    class SegmentDescriptor {
        private:
            matidigo::types::uint16_t limit_lo;
            matidigo::types::uint16_t base_lo;
            matidigo::types::uint8_t base_hi;
            matidigo::types::uint8_t type;
            matidigo::types::uint8_t limit_hi;
            matidigo::types::uint8_t base_vhi;

        public:
            SegmentDescriptor(matidigo::types::uint32_t base, matidigo::types::uint32_t limit, matidigo::types::uint8_t type);
            
            matidigo::types::uint32_t Base();
            matidigo::types::uint32_t Limit();
    
    } __attribute__((packed));

    class GlobalDescriptorTable
    {
        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();

            matidigo::types::uint16_t CodeSegmentSelector();
            matidigo::types::uint16_t DataSegmentSelector();
        
        private:
            SegmentDescriptor code_segment_selector;
            SegmentDescriptor null_segment_selector;
            SegmentDescriptor data_segment_selector;
            SegmentDescriptor unused_segment_selector;
    };
}

#endif