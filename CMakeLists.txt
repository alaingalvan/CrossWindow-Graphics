# Project Info

cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
cmake_policy(VERSION 3.6)
project(CrossWindowGraphics
        VERSION 1.0.0.0
        LANGUAGES C CXX
)

# =============================================================

# Options

set(XGFX_API AUTO CACHE STRING "The graphics API you're targeting, defaults to VULKAN, can be VULKAN, OPENGL, DIRECTX12, DIRECTX11, METAL, or NONE.")
set_property(
    CACHE
    XGFX_API PROPERTY
    STRINGS VULKAN OPENGL DIRECTX12 DIRECTX11 METAL
)

if(XGFX_API STREQUAL "VULKAN")
    set(XGFX_API_PATH "Vulkan")
elseif(XGFX_API STREQUAL "OPENGL")
    set(XGFX_API_PATH "OpenGL")
elseif(XGFX_API STREQUAL "DIRECTX12")
    set(XGFX_API_PATH "DirectX 12")
elseif(XGFX_API STREQUAL "DIRECTX11")
    set(XGFX_API_PATH "DirectX 11")
elseif(XGFX_API STREQUAL "METAL")
    set(XGFX_API_PATH "Metal")
elseif(XGFX_API STREQUAL "NONE")
    set(XGFX_API_PATH "None")
else()
    message( SEND_ERROR "XGFX_API can only be either VULKAN, OPENGL, DIRECTX12, DIRECTX11, METAL, or NONE.")
endif()

# =============================================================

# Finalize Library

add_library(CrossWindowGraphics INTERFACE)

target_include_directories(
  CrossWindowGraphics INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(NOT( XGFX_API STREQUAL "NONE" ))
    message( STATUS "Using the " ${XGFX_API_PATH} " graphics API with CrossWindow")
    target_compile_definitions(CrossWindowGraphics INTERFACE XGFX_${XGFX_API}=1)
else()
    message( STATUS "Not adding preprocessor definitions to CrossWindowGraphics")
endif()

