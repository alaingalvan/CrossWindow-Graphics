#pragma once

#if defined(XGFX_METAL) && (defined(XWIN_COCOA) || defined(XWIN_UIKIT))
namespace xwin
{
  CAMetalLayer* createMetalLayer(Window* window)
  {
	  const xwin::WindowDelegate& del = window->getDelegate();
	  del.setLayer(xwin::WindowDelegate::LayerType::Metal);
	  return del.layer;
  }
}
#endif
