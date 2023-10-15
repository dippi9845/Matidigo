 
#ifndef __MATIDIGO__GUI__WINDOW_H
#define __MATIDIGO__GUI__WINDOW_H

#include "widget.h"
#include "../drivers/mouse.h"

namespace matidigo
{
    namespace gui
    {
        
        class Window : public CompositeWidget
        { 
        protected:
            bool Dragging;
            
        public:
            Window(Widget* parent,
                   types::int32_t x, types::int32_t y, types::int32_t w, types::int32_t h,
                   types::uint8_t r, types::uint8_t g, types::uint8_t b);
            ~Window();

            void OnMouseDown(types::int32_t x, types::int32_t y, types::uint8_t button);
            void OnMouseUp(types::int32_t x, types::int32_t y, types::uint8_t button);
            void OnMouseMove(types::int32_t oldx, types::int32_t oldy, types::int32_t newx, types::int32_t newy);
            
        };
    }
}

#endif