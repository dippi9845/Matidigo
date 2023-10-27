 
#ifndef __MATIDIGO__GUI__DESKTOP_H
#define __MATIDIGO__GUI__DESKTOP_H

#include "widget.h"
#include "../drivers/mouse.h"

namespace matidigo
{
    namespace gui
    {
        
        class Desktop : public CompositeWidget, public matidigo::drivers::MouseEventHandler
        {
        protected:
            types::uint32_t MouseX;
            types::uint32_t MouseY;
            
        public:
            Desktop(types::int32_t w, types::int32_t h,
                types::uint8_t r, types::uint8_t g, types::uint8_t b);
            ~Desktop();
            
            void Draw(matidigo::types::GraphicsContext* gc);
            
            void OnMouseDown(matidigo::types::uint8_t button);
            void OnMouseUp(matidigo::types::uint8_t button);
            void OnMouseMove(int x, int y);
        };
        
    }
}


#endif