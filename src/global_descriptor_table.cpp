#include "global_descriptor_table.h"

using namespace matidigo;
using namespace matidigo::types;

SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type) {
    uint8_t* target = (uint8_t*)this;

    if (limit <= MAX_ADDRESSABLE_16BIT_MEMORY) {
        // 16-bit address space
        target[6] = 0x40;
    }

    else {
        /*
        32-bit address space
        Now we have to fit the (32-bit) limit into 2.5 registers (20-bit).
        This is achieved by discarding the 12 least significant bits. However, this is only valid
        if they are all set to 1; hence, they are implicitly retained.
        Therefore, if the last bits are not all set to 1, we need to set them to 1.
        But doing so would increase the limit (which is not allowed since it might exceed
        the physical limit or overlap with other segments). To compensate for this,
        we need to reduce a higher bit (which may result in up to 4095 unused bytes beyond the allocated memory).
        */

        if((limit & FIRST_12_ONES) != FIRST_12_ONES)
            limit = (limit >> 12)-1;
        else
            limit = limit >> 12;

        target[6] = 0xC0;
    }

    // Encode the limit

    // alternative to this pointer
    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    // Encode the base

    // alternative to this pointer
    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    // Type
    target[5] = type;
}

uint32_t SegmentDescriptor::Base() {
}

uint32_t SegmentDescriptor::Limit() {
}

matidigo::GlobalDescriptorTable::GlobalDescriptorTable() {
    this->null_segment_selector = SegmentDescriptor(0, 0, 0);
    this->unused_segment_selector = SegmentDescriptor(0, 0, 0);
    this->code_segment_selector = SegmentDescriptor(0, 64*1024*1024, 0x9A);
    this->data_segment_selector = SegmentDescriptor(0, 64*1024*1024, 0x92);

    uint32_t j[2];
    j[1] = (uint32_t)this;
    j[0] = sizeof(GlobalDescriptorTable) << 16;
    
    // load the GDT
    asm volatile("lgdt (%0)": :"p" (((uint8_t *) j)+2));
}

matidigo::GlobalDescriptorTable::~GlobalDescriptorTable() {
}

uint16_t matidigo::GlobalDescriptorTable::CodeSegmentSelector() {
    return (uint8_t*)&this->code_segment_selector - (uint8_t*)this;
}

uint16_t matidigo::GlobalDescriptorTable::DataSegmentSelector() {
    return (uint8_t*)&this->data_segment_selector - (uint8_t*)this;
}
