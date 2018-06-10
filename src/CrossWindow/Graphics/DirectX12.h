#pragma once

#if defined(XGFX_DIRECTX12) && defined(XWIN_WINDOWS)
namespace xwin
{
  ComPtr<IDXGISwapChain1> createSwapchain(Window* window, ComPtr<IDXGIFactory4> factory, ComPtr<ID3D12CommandQueue> queue)
  {
    WindowDelegate delegate = window->getDelegate();

    // Describe and create the swapchain.
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
    swapChainDesc.BufferCount = FrameCount;
    swapChainDesc.Width = delegate.desc->width;
    swapChainDesc.Height = delegate.desc->height;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapChainDesc.SampleDesc.Count = 1;

    ComPtr<IDXGISwapChain1> swapchain;
    ThrowIfFailed(factory->CreateSwapChainForHwnd(
      queue.Get(),		// Swap chain needs the queue so that it can force a flush on it.
      delegate.hwnd,
      &swapChainDesc,
      nullptr,
      &swapchain
      ));

    ThrowIfFailed(swapChain.As(&m_swapChain));

    return swapchain;
  }
}
#endif