#pragma once

#if defined(XGFX_VULKAN)

#if defined(XWIN_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(XWIN_COCOA)
#define VK_USE_PLATFORM_MACOS_MVK
#elif defined(XWIN_UIKIT)
#define VK_USE_PLATFORM_IOS_MVK
#elif defined(XWIN_XCB)
#define VK_USE_PLATFORM_XCB_KHR
#elif defined(XWIN_ANDROID)
#define VK_USE_PLATFORM_ANDROID_KHR
#endif

#include "vulkan/vulkan.hpp"


namespace xgfx
{

inline vk::SurfaceKHR getSurface(xwin::Window* window, vk::Instance& instance)
{

    xwin::WindowDelegate& del = window->getDelegate();

    VkSurfaceKHR surface;
    VkResult result = VK_RESULT_MAX_ENUM;

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR info;
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.pNext = NULL;
    info.flags = 0;
    info.hinstance = del.hinstance;
    info.hwnd = del.hwnd;

    result = vkCreateWin32SurfaceKHR(static_cast<VkInstance>(instance), &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkWaylandSurfaceCreateInfoKHR info;
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.display = del.display;
    createInfo.surface = del.window;

    result = vkCreateWaylandSurfaceKHR(static_cast<VkInstance>(instance), &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_MIR_KHR)
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkAndroidSurfaceCreateInfoKHR info;
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.window = (ANativeWindow *)(del.window);

    result = vkCreateAndroidSurfaceKHR(static_cast<VkInstance>(instance), &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
    VkXlibSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.dpy = del.display;
    createInfo.window = del.window;

    result = vkCreateXlibSurfaceKHR(static_cast<VkInstance>(instance), &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.connection = del.connection;
    createInfo.window = del.window;

    result = vkCreateXcbSurfaceKHR(static_cast<VkInstance>(instance), &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
    err = demo_create_display_surface(demo);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
    VkIOSSurfaceCreateInfoMVK surface;
    surface.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    surface.pNext = NULL;
    surface.flags = 0;
    surface.pView = del.view;

    result = vkCreateIOSSurfaceMVK(static_cast<VkInstance>(instance), &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
	
	del.setLayer(xwin::WindowDelegate::LayerType::Metal);
	
    VkMacOSSurfaceCreateInfoMVK info;
    info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    info.pNext = NULL;
    info.flags = 0;
    info.pView = del.view;

    result = vkCreateMacOSSurfaceMVK(static_cast<VkInstance>(instance), &info, NULL, &surface);
#endif
    if (result == VK_SUCCESS)
    {
        return vk::SurfaceKHR(surface);
    }
    else
    {
        //throw error
    }
    return vk::SurfaceKHR();
}
}
#endif
