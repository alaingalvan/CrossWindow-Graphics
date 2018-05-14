#pragma once

#if defined(XWIN_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#if defined(XWIN_MACOS)
#define VK_USE_PLATFORM_MACOS_MVK
#if defined(XWIN_LINUX)
#define VK_USE_PLATFORM_WAYLAND_KHR
#if defined(XWIN_IOS)
#define VK_USE_PLATFORM_IOS_MVK
#if defined(XWIN_ANDROID)
#define VK_USE_PLATFORM_ANDROID_KHR
#endif

#include "vulkan/vulkan.hpp"

namespace xwin
{

vk::SurfaceKHR getSurface(xwin::Window* window, vk::Instance &instance)
{

    WindowDelegate delegate = window->getDelegate();

    VkSurfaceKHR surface;
    VkResult result = VK_RESULT_MAX_ENUM;

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR info;
    info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    info.pNext = NULL;
    info.flags = 0;
    info.hinstance = reinterpret_cast<HINSTANCE>(delegate->hinstance);
    info.hwnd = delegate->hwnd;

    result = vkCreateWin32SurfaceKHR(instance, &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkWaylandSurfaceCreateInfoKHR info;
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.display = delegate->display;
    createInfo.surface = delegate->window;

    result = vkCreateWaylandSurfaceKHR(instance, &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_MIR_KHR)
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkAndroidSurfaceCreateInfoKHR info;
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.window = (ANativeWindow *)(delegate->window);

    result = vkCreateAndroidSurfaceKHR(instance, &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
    VkXlibSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.dpy = delegate->display;
    createInfo.window = delegate->xlib_window;

    result = vkCreateXlibSurfaceKHR(instance, &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.connection = delegate->connection;
    createInfo.window = delegate->xcb_window;

    result = vkCreateXcbSurfaceKHR(instance, &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
    err = demo_create_display_surface(demo);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
    VkIOSSurfaceCreateInfoMVK surface;
    surface.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    surface.pNext = NULL;
    surface.flags = 0;
    surface.pView = delegate->window;

    result = vkCreateIOSSurfaceMVK(instance, &info, NULL, &surface);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
    VkMacOSSurfaceCreateInfoMVK info;
    info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    info.pNext = NULL;
    info.flags = 0;
    info.pView = delegate->window;

    result = vkCreateMacOSSurfaceMVK(instance, &info, NULL, &surface);
#endif
    if (result == VK_SUCCESS)
    {
        return vk::SurfaceKHR(surface);
    }
    return vk::SurfaceKHR();
}
}