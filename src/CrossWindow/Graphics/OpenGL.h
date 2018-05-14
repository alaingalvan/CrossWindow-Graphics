#pragma once

namespace xwin
{
#if defined(XWIN_WINDOWS)
HGLRC createContext(Window *window)
{
  WindowDelegate delegate = window->getDelegate();

  PIXELFORMATDESCRIPTOR pfd =
      {
          sizeof(PIXELFORMATDESCRIPTOR),
          1,
          PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
          PFD_TYPE_RGBA,                                              //The kind of framebuffer. RGBA or palette.
          32,                                                         //Colordepth of the framebuffer.
          0, 0, 0, 0, 0, 0,
          0,
          0,
          0,
          0, 0, 0, 0,
          24, //Number of bits for the depthbuffer
          8,  //Number of bits for the stencilbuffer
          0,  //Number of Aux buffers in the framebuffer.
          PFD_MAIN_PLANE,
          0,
          0, 0, 0};

  HDC ourWindowHandleToDeviceContext = GetDC(delegate->hwnd);

  int letWindowsChooseThisPixelFormat;
  letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
  SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

  //👇 The Key!
  HGLRC context = wglCreateContext(ourWindowHandleToDeviceContext);
  wglMakeCurrent(ourWindowHandleToDeviceContext, context);

  return context;
}

bool destroyContext(HGLRC context)
{
  wglDeleteContext(context);
  return true;
}
#endif
}