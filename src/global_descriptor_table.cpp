#include "global_descriptor_table.h"

using namespace matidigo;
using namespace matidigo::types;

SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type) {
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
    asm volatile("lgdt (%0)": :"p" (((uint8_t *) j)+2));
}

matidigo::GlobalDescriptorTable::~GlobalDescriptorTable() {
}

matidigo::types::uint16_t matidigo::GlobalDescriptorTable::CodeSegmentSelector() {
    return matidigo::types::uint16_t();
}

matidigo::types::uint16_t matidigo::GlobalDescriptorTable::DataSegmentSelector() {
    return matidigo::types::uint16_t();
}
