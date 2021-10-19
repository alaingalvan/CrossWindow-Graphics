#pragma once

#if (defined(XWIN_WIN32) || defined(XWIN_UWP)) && defined(XGFX_DIRECTX12)

#include "d3d12.h"
#include <D3Dcompiler.h>
#include <dxgi1_4.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace xgfx
{
inline IDXGISwapChain1*
    createSwapchain(xwin::Window* window, IDXGIFactory4* factory,
                    ID3D12CommandQueue* queue,
                    DXGI_SWAP_CHAIN_DESC1* swapchainDesc,
                    DXGI_SWAP_CHAIN_FULLSCREEN_DESC* fullscreenDesc = nullptr,
                    IDXGIOutput* output = nullptr)
{
    IDXGISwapChain1* swapchain = nullptr;
    HRESULT hr = factory->CreateSwapChainForHwnd(
        queue, window->getHwnd(), swapchainDesc, fullscreenDesc, output, &swapchain);

    if (!FAILED(hr))
    {
        return swapchain;
    }

    return nullptr;
}
}
#endif