#pragma once

#if defined(XGFX_METAL) && (defined(XWIN_COCOA) || defined(XWIN_UIKIT))

namespace xgfx
{
inline void createMetalLayer(xwin::Window* window)
{
    window->setLayer(xwin::WindowDelegate::LayerType::Metal);
}
}
#endif
