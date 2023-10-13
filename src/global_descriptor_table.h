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

}