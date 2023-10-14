#ifndef __MATIDIGO__GLOBAL_DESCRIPTOR_TABLE__H
#define __MATIDIGO__GLOBAL_DESCRIPTOR_TABLE__H

#define MAX_ADDRESSABLE_16BIT_MEMORY 0x10000
#define FIRST_12_ONES 0xFFF

#define LIMIT_LOWER_BYTE_LOWER 0
#define LIMIT_LOWER_BYTE_UPPER 1
#define LIMIT_UPPER_BYTE 6

#define BASE_LOWER_BYTE_LOWER 2
#define BASE_LOWER_BYTE_UPPER 3
#define BASE_UPPER_BYTE_LOWER 4
#define BASE_UPPER_BYTE_UPPER 7

#define TYPE 5

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