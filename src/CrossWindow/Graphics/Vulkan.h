#pragma once

#if defined(XGFX_VULKAN)

#if defined(XWIN_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#elif defined(XWIN_COCOA)
#define VK_USE_PLATFORM_MACOS_MVK
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_MVK_MACOS_SURFACE_EXTENSION_NAME
#elif defined(XWIN_UIKIT)
#define VK_USE_PLATFORM_IOS_MVK
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_MVK_IOS_SURFACE_EXTENSION_NAME
#elif defined(XWIN_XCB)
#define VK_USE_PLATFORM_XCB_KHR
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_KHR_XCB_SURFACE_EXTENSION_NAME
#elif defined(XWIN_XLIB)
#define VK_USE_PLATFORM_XLIB_KHR
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_KHR_XLIB_SURFACE_EXTENSION_NAME
#elif defined(XWIN_WAYLAND)
#define VK_USE_PLATFORM_WAYLAND_KHR
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME
#elif defined(XWIN_MIR)
#define VK_USE_PLATFORM_MIR_KHR
#define VK_USE_PLATFORM_DISPLAY_KHR
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_KHR_DISPLAY_EXTENSION_NAME
#elif defined(XWIN_ANDROID)
#define VK_USE_PLATFORM_ANDROID_KHR
#define VK_XWIN_SURFACE_EXTENSION_NAME VK_KHR_ANDROID_SURFACE_EXTENSION_NAME
#endif

#include "vulkan/vulkan.hpp"

namespace xgfx
{

inline vk::SurfaceKHR createSurface(xwin::Window* window,
                                    vk::Instance instance)
{
    VkSurfaceKHR surface;
    VkResult result = VK_RESULT_MAX_ENUM;

#if defined(VK_USE_PLATFORM_WIN32_KHR)
    VkWin32SurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.hinstance = window->hinstance;
    createInfo.hwnd = window->hwnd;

    result = vkCreateWin32SurfaceKHR(static_cast<VkInstance>(instance),
                                     &createInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
    VkWaylandSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.display = window->display;
    createInfo.surface = window->window;

    result = vkCreateWaylandSurfaceKHR(static_cast<VkInstance>(instance),
                                       &createInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_MIR_KHR)
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
    VkAndroidSurfaceCreateInfoKHR craeteInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.window = (ANativeWindow*)(window->window);

    result = vkCreateAndroidSurfaceKHR(static_cast<VkInstance>(instance),
                                       &createInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
    VkXlibSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.dpy = window->display;
    createInfo.window = window->window;

    result = vkCreateXlibSurfaceKHR(static_cast<VkInstance>(instance),
                                    &createInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
    VkXcbSurfaceCreateInfoKHR createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.connection = window->connection;
    createInfo.window = window->window;

    result = vkCreateXcbSurfaceKHR(static_cast<VkInstance>(instance),
                                   &createInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_DISPLAY_KHR)
    err = demo_create_display_surface(demo);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
    VkIOSSurfaceCreateInfoMVK createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_IOS_SURFACE_CREATE_INFO_MVK;
    createInfo.pNext = NULL;
    createInfo.flags = 0;
    createInfo.pView = window->view;

    result = vkCreateIOSSurfaceMVK(static_cast<VkInstance>(instance),
                                   &createInfo, NULL, &surface);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)

    window->setLayer(xwin::WindowDelegate::LayerType::Metal);

    VkMacOSSurfaceCreateInfoMVK createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    createinfo.pNext = NULL;
    createinfo.flags = 0;
    createinfo.pView = window->view;

    result = vkCreateMacOSSurfaceMVK(static_cast<VkInstance>(instance),
                                     &createInfo, NULL, &surface);
#endif
    if (result == VK_SUCCESS) return vk::SurfaceKHR(surface);
    return vk::SurfaceKHR();
}
}
#endif
