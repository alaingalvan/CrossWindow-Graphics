#pragma once

#if defined(XGFX_METAL) && (defined(XWIN_COCOA) || defined(XWIN_UIKIT))
namespace xwin
{
  CAMetalLayer* createMetalLayer(Window* window)
  {
        const xwin::WindowDelegate& del = window->getDelegate();
        [del.view setWantsLayer:Yes];
        CAMetalLayer* layer = [[CAMetalLayer init];
        [del.view setLayer:layer];
        return layer;
  }
}
#endif