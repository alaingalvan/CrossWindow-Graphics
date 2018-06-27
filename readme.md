# CrossWindow-Graphics

[![cmake-img]][cmake-url]
[![License][license-img]][license-url]

A header only library to simplify creating and managing data structures needed for graphics APIs such as a Vulkan `vk::Surface`, an OpenGL context, a DirectX `IDXGISwapChain1`, or Metal `CAMetalLayer`.

## Supports

 - 🌋 Vulkan
 - ⚪ OpenGL 4.x / OpenGL ES 3.x / 🌐 WebGL
 - ❎DirectX 12 / 11
 - 🤖 Metal

## Installation

First add the repo as a submodule in your dependencies folder such as `external/`:

```
cd external
git submodule add https://github.com/alaingalvan/crosswindow-graphics.git
```

Then in your `CMakeLists.txt` file, include the following:

```cmake
add_subdirectory(external/crosswindow-graphics)

# 🤯 CrossWindowGraphics is a header only library, so no polluting your project list.
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

  // ⚪ OpenGL 4.x / OpenGL ES 3.x / 🌐 WebGL platform specific context data
  xwin::OpenGLDesc desc;
  xwin::OpenGLState state = xwin::createContext(&window, desc);

  xwin::setContext(state);

  xwin::swapBuffers(state);

  xwin::unsetContext(state);

  xwin::destroyContext(state);

#elif defined(XGFX_DIRECTX12)

  // ❎ DirectX 12 Swapchain
  IDXGISwapChain1* swapchain = xgfx::createSwapchain(window, factory, commandQueue, &swapchainDesc);

#elif defined(XGFX_DIRECTX11)

  // ❌ DirectX 11 Swapchain
  IDXGISwapChain* swapchain = xgfx::createSwapchain(window, factory, device, &swapchainDesc);

#elif defined(XWIN_METAL)

  // 🤖 Metal Layer
  xwin::createMetalLayer(&window);

#endif
}

```

### Preprocessor Definitions

| CMake Options | Description |
|:-------------:|:-----------:|
| `XGFX_PROTOCOL` | The protocol to use for your graphics API, defaults to `VULKAN`, can be can be `VULKAN`, `OPENGL`, `DIRECTX12`, `METAL`, or `NONE`. |

Alternatively you can set the following preprocessor definitions manually:

| Definition | Description |
|:-------------:|:-----------:|
| `XGFX_VULKAN` |  Vulkan 1.x. |
| `XGFX_OPENGL` |  OpenGL 4.x and OpenGL ES 3.x. |
| `XGFX_DIRECTX12` | DirectX 12.x. |
| `XGFX_DIRECTX11` | DirectX 11.x. |
| `XGFX_METAL` | Metal 1 or 2. |

## Design Decisions

The official Khronos Group's Vulkan Samples features an [OpenGL driver info example](https://github.com/KhronosGroup/Vulkan-Samples/blob/master/samples/apps/driverinfo/driverinfo_opengl.c) and [Vulkan cube example](https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/blob/master/demos/cube.c) that the OpenGL/Vulkan portions of this library pull heavily from, but diverges with the decision to separate operating systems by protocol (similar to the design of CrossWindow).

You can read more [in our docs](docs/design-decisions.md).

## License

CrossWindow is licensed as either **MIT** or **Apache-2.0**, whichever you would prefer.

[cmake-img]: https://img.shields.io/badge/cmake-3.6-1f9948.svg?style=flat-square
[cmake-url]: https://cmake.org/
[license-img]: https://img.shields.io/:license-mit-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT