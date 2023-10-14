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
    target[LIMIT_LOWER_BYTE_LOWER] = limit & 0xFF;
    target[LIMIT_LOWER_BYTE_UPPER] = (limit >> 8) & 0xFF;
    target[LIMIT_UPPER_BYTE] |= (limit >> 16) & 0xF;

    // Encode the base

    // alternative to this pointer
    target[BASE_LOWER_BYTE_LOWER] = base & 0xFF;
    target[BASE_LOWER_BYTE_UPPER] = (base >> 8) & 0xFF;
    target[BASE_UPPER_BYTE_LOWER] = (base >> 16) & 0xFF;
    target[BASE_UPPER_BYTE_UPPER] = (base >> 24) & 0xFF;

    // Type
    target[TYPE] = type;
}

uint32_t SegmentDescriptor::Base() {
    uint8_t* target = (uint8_t*)this;

    uint32_t result = target[BASE_UPPER_BYTE_UPPER];
    result = (result << 8) + target[BASE_UPPER_BYTE_LOWER];
    result = (result << 8) + target[BASE_LOWER_BYTE_UPPER];
    result = (result << 8) + target[BASE_LOWER_BYTE_LOWER];

    return result;
}

uint32_t SegmentDescriptor::Limit() {
    uint8_t* target = (uint8_t*)this;

    uint32_t result = target[LIMIT_UPPER_BYTE] & 0xF;
    result = (result << 8) + target[LIMIT_LOWER_BYTE_UPPER];
    result = (result << 8) + target[LIMIT_LOWER_BYTE_LOWER];

    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;

    return result;
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
