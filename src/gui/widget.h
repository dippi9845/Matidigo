 
#ifndef __MATIDIGO__GUI__WIDGET_H
#define __MATIDIGO__GUI__WIDGET_H


#include "../types.h"
#include "../graphicscontext.h"
#include "../drivers/keyboard.h"

namespace matidigo
{
    namespace gui
    {
        
        class Widget : public matidigo::drivers::KeyboardEventHandler
        {
        protected:
            Widget* parent;
            types::int32_t x;
            types::int32_t y;
            types::int32_t w;
            types::int32_t h;
            
            types::uint8_t r;
            types::uint8_t g;
            types::uint8_t b;
            bool Focussable;

        public:

            Widget(Widget* parent,
                   types::int32_t x, types::int32_t y, types::int32_t w, types::int32_t h,
                   types::uint8_t r, types::uint8_t g, types::uint8_t b);
            ~Widget();
            
            virtual void GetFocus(Widget* widget);
            virtual void ModelToScreen(types::int32_t &x, types::int32_t& y);
            virtual bool ContainsCoordinate(types::int32_t x, types::int32_t y);
            
            virtual void Draw(matidigo::types::GraphicsContext* gc);
            virtual void OnMouseDown(types::int32_t x, types::int32_t y, types::uint8_t button);
            virtual void OnMouseUp(types::int32_t x, types::int32_t y, types::uint8_t button);
            virtual void OnMouseMove(types::int32_t oldx, types::int32_t oldy, types::int32_t newx, types::int32_t newy);
        };
        
        
        class CompositeWidget : public Widget
        {
        private:
            Widget* children[100];
            int numChildren;
            Widget* focussedChild;
            
        public:
            CompositeWidget(Widget* parent,
                   types::int32_t x, types::int32_t y, types::int32_t w, types::int32_t h,
                   types::uint8_t r, types::uint8_t g, types::uint8_t b);
            ~CompositeWidget();            
            
            virtual void GetFocus(Widget* widget);
            virtual bool AddChild(Widget* child);
            
            virtual void Draw(matidigo::types::GraphicsContext* gc);
            virtual void OnMouseDown(types::int32_t x, types::int32_t y, types::uint8_t button);
            virtual void OnMouseUp(types::int32_t x, types::int32_t y, types::uint8_t button);
            virtual void OnMouseMove(types::int32_t oldx, types::int32_t oldy, types::int32_t newx, types::int32_t newy);
            
            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };
        
    }
}


#endif