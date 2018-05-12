# CrossWindow-Graphics

A library to simplify creating data structures needed for graphics APIs such as a Vulkan `vk::Surface`, an OpenGL context, a DirectX `ComPtr<IDXGISwapChain>`, or Metal `MTLView`.

## Supports

 - 🌋 Vulkan 
 - ⚪ OpenGL 4.x / 🌐 WebGL
 - ❎DirectX 12
 - 🤖 Metal 2 

## Installation

First add the repo as a submodule in your dependencies folder such as `external/`:

```
cd external
git submodule add https://github.com/alaingalvan/CrossWindow-Graphics.git
```

Then in your `CMakeLists.txt` file, include the following:

```cmake
# ⬇ Add your dependency:
add_subdirectories(external/CrossWindow-Graphics)

# 🤯 Since it's a header only library, you just need to include the headers!
target_include_directories(exteral/CrossWIndow-Graphics/src)

# Set up CrossWindow as usual...
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
  
#if defined(XWIN_VULKAN)
  vk::Surface surface = xwin::createSurface(window, instance);
#elif defined(XWIN_OPENGL)
 // ...
#elif defined(XWIN_DIRECTX)
  ComPtr<IDXGISwapChain1> swapchain = xwin::createSwapchain(instance, factory);
#elif defined(XWIN_METAL)
 // ...
#endif
}

```

## Development

Be sure to have [CMake](https://cmake.org) Installed.

| CMake Options | Description |
|:-------------:|:-----------:|
| `XWIN_GRAPHICS_API` | Whether or not unit tests are enabled. Defaults to `VULKAN`, Can be `VULKAN`, `DIRECTX`, `METAL` or `OPENGL` depending on `XWIN_OS`. |
