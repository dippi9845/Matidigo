 
#include "window.h"

using namespace matidigo::types;
using namespace matidigo::gui;

Window::Window(Widget* parent,
            types::int32_t x, types::int32_t y, types::int32_t w, types::int32_t h,
            types::uint8_t r, types::uint8_t g, types::uint8_t b)
: CompositeWidget(parent, x,y,w,h, r,g,b)
{
    Dragging = false;
}

Window::~Window()
{
}

void Window::OnMouseDown(types::int32_t x, types::int32_t y, types::uint8_t button)
{
    Dragging = button == 1;
    CompositeWidget::OnMouseDown(x,y,button);
}

void Window::OnMouseUp(types::int32_t x, types::int32_t y, types::uint8_t button)
{
    Dragging = false;
    CompositeWidget::OnMouseUp(x,y,button);
}

void Window::OnMouseMove(types::int32_t oldx, types::int32_t oldy, types::int32_t newx, types::int32_t newy)
{
    if(Dragging)
    {
        this->x += newx-oldx;
        this->y += newy-oldy;
    }
    CompositeWidget::OnMouseMove(oldx,oldy,newx, newy);

}

    
