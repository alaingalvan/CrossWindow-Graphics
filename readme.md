# CrossWindow-Graphics

[![cmake-img]][cmake-url]
[![License][license-img]][license-url]

A header only library to simplify creating and managing data structures needed for graphics APIs such as a Vulkan `vk::Surface`, an OpenGL context, a DirectX `IDXGISwapChain1`, or Metal `CAMetalLayer`.

## Supports

 - 🌋 Vulkan
 - ⚪ OpenGL
 - ⚪ OpenGL ES
 - 🌐 WebGL
 - ❎ DirectX 12.x
 - ✖️ DirectX 11.x
 - 🤖 Metal

## Installation

First add the repo as a submodule in your dependencies folder such as `external/`:

```bash
cd external
git submodule add https://github.com/alaingalvan/crosswindow-graphics.git
```

Then in your `CMakeLists.txt` file, include the following:

```cmake
add_subdirectory(external/crosswindow-graphics)

target_link_libraries(
    ${PROJECT_NAME}
    CrossWindowGraphics
)
```

## Usage

```cpp
#include "CrossWindow/CrossWindow.h"
#include "CrossWindow/Graphics.h

void xmain(int argc, char** argv)
{
  // 🖼️ Create your xwin::Window...
  xwin::Window window;
  
  // ...
  
#if defined(XGFX_VULKAN)
  
  // 🌋 Vulkan Surface
  vk::Surface surface = xwin::createSurface(&window, instance);

#elif defined(XGFX_OPENGL)

  // ⚪ OpenGL / OpenGL ES / 🌐 WebGL platform specific context data
  xwin::OpenGLDesc desc;
  xwin::OpenGLState state = xwin::createContext(&window, desc);

  // ⬇️ Set the context
  xwin::setContext(state);

  // 🔀 Refresh your window
  xwin::swapBuffers(state);

  // ⬆️ Unset the context
  xwin::unsetContext(state);

  // ⬅️ Destroy the context
  xwin::destroyContext(state);

#elif defined(XGFX_DIRECTX12)

  // ❎ DirectX 12.x Swapchain
  IDXGISwapChain1* swapchain = xgfx::createSwapchain(window, factory, commandQueue, &swapchainDesc);

#elif defined(XGFX_DIRECTX11)

  // ✖️ DirectX 11.x Swapchain
  IDXGISwapChain* swapchain = xgfx::createSwapchain(window, factory, device, &swapchainDesc);

#elif defined(XWIN_METAL)

  // 🤖 Metal Layer
  xwin::createMetalLayer(&window);

  // 🍮 Access the layer from your window
  CAMetalLayer* layer = (CAMetalLayer*)window.getDelegate().layer;

#endif
}

```

### Preprocessor Definitions

| CMake Options | Description |
|:-------------:|:-----------:|
| `XGFX_API` | The graphics API you're targeting, defaults to `VULKAN`, can be can be `VULKAN`, `OPENGL`, `DIRECTX12`, `METAL`, or `NONE`. |

Alternatively you can set the following preprocessor definitions manually:

| Definition | Description |
|:-------------:|:-----------:|
| `XGFX_VULKAN` |  Vulkan |
| `XGFX_OPENGL` |  OpenGL / OpenGL ES / WebGL |
| `XGFX_DIRECTX12` | DirectX 12.x |
| `XGFX_DIRECTX11` | DirectX 11.x |
| `XGFX_METAL` | Metal |

## Design Decisions

The official Khronos Group's Vulkan Samples features an [OpenGL driver info example](https://github.com/KhronosGroup/Vulkan-Samples/blob/master/samples/apps/driverinfo/driverinfo_opengl.c) and [Vulkan cube example](https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/blob/master/demos/cube.c) that the OpenGL/Vulkan portions of this library pull heavily from, but diverges with the decision to separate operating systems by protocol (similar to the design of CrossWindow).

You can read more [in our docs](docs/design-decisions.md).

## License

CrossWindow is licensed as either **MIT** or **Apache-2.0**, whichever you would prefer.

[cmake-img]: https://img.shields.io/badge/cmake-3.6-1f9948.svg?style=flat-square
[cmake-url]: https://cmake.org/
[license-img]: https://img.shields.io/:license-mit-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT