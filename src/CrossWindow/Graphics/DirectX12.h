#pragma once

#if ( defined(XWIN_WIN32) || defined(XWIN_UWP) ) && defined(XGFX_DIRECTX12)
namespace xwin
{
  inline ComPtr<IDXGISwapChain1> createSwapchain(Window* window, ComPtr<IDXGIFactory4> factory, ComPtr<ID3D12CommandQueue> queue, DXGI_SWAP_CHAIN_DESC1* swapchainDesc)
  {
    WindowDelegate delegate = window->getDelegate();

    ComPtr<IDXGISwapChain1> swapchain;
    HRESULT hr = factory->CreateSwapChainForHwnd(
      queue.Get(),		// Swap chain needs the queue so that it can force a flush on it.
      delegate.hwnd,
      swapChainDesc,
      nullptr,
      &swapchain
      ));

    if ( !FAILED(hr) )
    {
      return swapchain;
    }

    return nullptr;
    }
}
#endif