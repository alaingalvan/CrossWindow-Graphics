# CrossWindow-Graphics

[![cmake-img]][cmake-url]
[![License][license-img]][license-url]

A header only library to simplify creating data structures needed for graphics APIs such as a Vulkan `vk::Surface`, an OpenGL context, a DirectX `ComPtr<IDXGISwapChain>`, or Metal `MTLView`.

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
add_subdirectory(external/crosswindow-graphics)

target_link_libraries(
    ${PROJECT_NAME}
    CrossWindowGraphics
)
```

Alternatively if you don't want an extra project in your solution, you can just include the directory and add preprocessor definitions to your project:

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

  vk::Surface surface = xwin::createSurface(&window, instance);

#elif defined(XGFX_OPENGL)
  // Platform specific context data can be found inside xwin::OpenGLState
  xwin::OpenGLDesc desc;
  xwin::OpenGLState state = xwin::createContext(&window, desc);

  xwin::setContext(state);

  xwin::unsetContext(state);

  xwin::destroyContext(state);

#elif defined(XGFX_DIRECTX12)

  ComPtr<IDXGISwapChain1> swapchain = xwin::createSwapchain(&window, factory, queue, &swapchainDesc);

#elif defined(XWIN_METAL)
  // A pointer to MTKView will only work on an `.mm` file:
  MTKView* view = xwin::createMetalView(&window);
  id<MTLDevice> device = view.device;
  // ...
#endif
}

```

### Preprocessor Definitions

| CMake Options | Description |
|:-------------:|:-----------:|
| `XGFX_PROTOCOL` | The protocol to use for your graphics API, defaults to `VULKAN`, can be can be `VULKAN`, `OPENGL`, `DIRECTX12`, or `METAL`. |

Alternatively you can set the following preprocessor definitions manually:

| Definition | Description |
|:-------------:|:-----------:|
| `XGFX_VULKAN` |  Vulkan 1.x. |
| `XGFX_OPENGL` |  OpenGL 4.x and OpenGL ES 3.x. |
| `XGFX_DIRECTX12` | DirectX 12.x. |
| `XGFX_METAL` | Metal 1 or 2. |

## Design Decisions

The official Khronos Group's Vulkan Samples features an [OpenGL driver info example](https://github.com/KhronosGroup/Vulkan-Samples/blob/master/samples/apps/driverinfo/driverinfo_opengl.c) and [Vulkan cube example](https://github.com/KhronosGroup/Vulkan-LoaderAndValidationLayers/blob/master/demos/cube.c) that the OpenGL/Vulkan portions of this library pull heavily from, but diverges with the decision to separate operating systems by protocol (similar to the design of CrossWindow).

## License

CrossWindow is licensed as either **MIT** or **Apache-2.0**, whichever you would prefer.

[cmake-img]: https://img.shields.io/badge/cmake-3.6-1f9948.svg?style=flat-square
[cmake-url]: https://cmake.org/
[license-img]: https://img.shields.io/:license-mit-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT