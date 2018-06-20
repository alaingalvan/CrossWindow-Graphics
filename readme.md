# CrossWindow-Graphics

[![License][license-img]][license-url]

A library to simplify creating data structures needed for graphics APIs such as a Vulkan `vk::Surface`, an OpenGL context, a DirectX `ComPtr<IDXGISwapChain>`, or Metal `MTLView`.

## Supports

 - 🌋 Vulkan
 - ⚪ OpenGL 4.x / OpenGL ES 3.x / 🌐 WebGL
 - ❎DirectX 12
 - 🤖 Metal 2 

## Installation

First add the repo as a submodule in your dependencies folder such as `external/`:

```
cd external
git submodule add https://github.com/alaingalvan/crosswindow-graphics.git
```

Then in your `CMakeLists.txt` file, include the following:

```cmake
# 🤯 Since it's a header only library, you just need to include the headers!
target_include_directories(exteral/crosswindow-graphics/src)

# Set up CrossWindow as usual...

# Make sure to add a preprocessor defintion for your target graphics API:
target_compile_definitions(${PROJECT_NAME} PRIVATE XGFX_VULKAN=1)
```

## Usage

```cpp
#include "CrossWindow/CrossWindow.h"
#include "CrossWindow/Graphics.h

void xmain(int argc, char** argv)
{
  // create your xwin::Window...
  xwin::Window window;
  
  // ...
  
#if defined(XGFX_VULKAN)

  vk::Surface surface = xwin::createSurface(window, instance);

#elif defined(XGFX_OPENGL)
  // Platform specific context data can be found inside xwin::OpenGLState
  xwin::OpenGLDesc desc;
  xwin::OpenGLState state = xwin::createContext(window, desc);

  xwin::setContext(state);

  xwin::unsetContext(state);

  xwin::destroyContext(state);

#elif defined(XGFX_DIRECTX12)

  ComPtr<IDXGISwapChain1> swapchain = xwin::createSwapchain(instance, factory);

#elif defined(XWIN_METAL)
  // A pointer to MTKView will only work on an `.mm` file:
  MTKView* view = xwin::createMetalView(window);
  id<MTLDevice> device = view.device;
  // ...
#endif
}

```

### Preprocessor Definitions

| Definition | Description |
|:-------------:|:-----------:|
| `XGFX_VULKAN` |  Vulkan 1.x. |
| `XGFX_OPENGL` |  OpenGL 4.x and OpenGL ES 3.x. |
| `XGFX_DIRECTX12` | DirectX 12.x. |
| `XGFX_METAL` | Metal 1 or 2. |

## License

CrossWindow is licensed as either **MIT** or **Apache-2.0**, whichever you would prefer.

[license-img]: https://img.shields.io/:license-mit-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT