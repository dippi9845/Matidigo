 

#ifndef __MATIDIGO__DRIVERS__VGA_H
#define __MATIDIGO__DRIVERS__VGA_H

#include "driver.h"
#include "../types.h"
#include "../hardware/port.h"

namespace matidigo
{
    namespace drivers
    {
        
        class VideoGraphicsArray
        {
        protected:
            hardware::Port8Bit miscPort;
            hardware::Port8Bit crtcIndexPort;
            hardware::Port8Bit crtcDataPort;
            hardware::Port8Bit sequencerIndexPort;
            hardware::Port8Bit sequencerDataPort;
            hardware::Port8Bit graphicsControllerIndexPort;
            hardware::Port8Bit graphicsControllerDataPort;
            hardware::Port8Bit attributeControllerIndexPort;
            hardware::Port8Bit attributeControllerReadPort;
            hardware::Port8Bit attributeControllerWritePort;
            hardware::Port8Bit attributeControllerResetPort;
            
            void WriteRegisters(types::uint8_t* registers);
            types::uint8_t* GetFrameBufferSegment();
            
            virtual types::uint8_t GetColorIndex(types::uint8_t r, types::uint8_t g, types::uint8_t b);
            
            
        public:
            VideoGraphicsArray();
            ~VideoGraphicsArray();
            
            virtual bool SupportsMode(types::uint32_t width, types::uint32_t height, types::uint32_t colordepth);
            virtual bool SetMode(types::uint32_t width, types::uint32_t height, types::uint32_t colordepth);
            virtual void PutPixel(types::int32_t x, types::int32_t y,  types::uint8_t r, types::uint8_t g, types::uint8_t b);
            virtual void PutPixel(types::int32_t x, types::int32_t y, types::uint8_t colorIndex);
            
            virtual void FillRectangle(types::uint32_t x, types::uint32_t y, types::uint32_t w, types::uint32_t h,   types::uint8_t r, types::uint8_t g, types::uint8_t b);

        };
        
    }
}

#endif