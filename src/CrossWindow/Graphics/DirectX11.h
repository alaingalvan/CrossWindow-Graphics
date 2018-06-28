#pragma once

#if ( defined(XWIN_WIN32) || defined(XWIN_UWP) ) && defined(XGFX_DIRECTX11)

#include "d3d11.h"
#include <dxgi1_2.h>
#include <D3Dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment	(lib, "d3dcompiler.lib")

namespace xgfx
{
    inline IDXGISwapChain* createSwapchain(xwin::Window* window, IDXGIFactory* factory, ID3D11Device* device, DXGI_SWAP_CHAIN_DESC* swapchainDesc)
    {
		xwin::WindowDelegate& del = window->getDelegate();
		xwin::WindowDesc desc = window->getDesc();

        swapchainDesc->OutputWindow = del.hwnd;
		swapchainDesc->Windowed = !desc.fullscreen;

        IDXGISwapChain* swapchain = nullptr;
        HRESULT hr = factory->CreateSwapChain(
            device,
            swapchainDesc,
            &swapchain
        );

        if (!FAILED(hr))
        {
            return swapchain;
        }

        return nullptr;
    }
}
#endif