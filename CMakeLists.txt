cmake_minimum_required(VERSION 3.6 FATAL_ERROR)
cmake_policy(VERSION 3.6)
project(CrossWindowGraphics
        VERSION 1.0.0.0
        LANGUAGES C CXX
        )

add_library(CrossWindowGraphics INTERFACE)

target_include_directories(
  CrossWindowGraphics INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)
set(XGFX_PROTOCOL AUTO CACHE STRING "A more specific platform selector to choose from, choose the exact graphics protocol to use, defaults to VULKAN, can be VULKAN, OPENGL, DIRECTX12, METAL, or NONE.")
set_property(
    CACHE
    XGFX_PROTOCOL PROPERTY
    STRINGS VULKAN OPENGL DIRECTX12 METAL
)

if(XGFX_PROTOCOL STREQUAL "AUTO")
  set(XGFX_PROTOCOL VULKAN)
endif()

if(XGFX_PROTOCOL STREQUAL "VULKAN")
    set(XGFX_PROTOCOL_PATH "Vulkan")
elseif(XGFX_PROTOCOL STREQUAL "OPENGL")
    set(XGFX_PROTOCOL_PATH "OpenGL")
elseif(XGFX_PROTOCOL STREQUAL "DIRECTX12")
    set(XGFX_PROTOCOL_PATH "DirectX 12")
elseif(XGFX_PROTOCOL STREQUAL "METAL")
    set(XGFX_PROTOCOL_PATH "Metal")
elseif(XGFX_PROTOCOL STREQUAL "NONE")
    set(XGFX_PROTOCOL_PATH "None")
else()
    message( SEND_ERROR "XGFX_PROTOCOL can only be either AUTO, VULKAN, OPENGL, DIRECTX12, or METAL.")
endif()

if(NOT( XGFX_PROTOCOL STREQUAL "NONE" ))
    message( STATUS "Using the " ${XGFX_PROTOCOL_PATH} " graphics API with CrossWindow")
    target_compile_definitions(CrossWindowGraphics INTERFACE XGFX_${XGFX_PROTOCOL}=1)
else()
    message( STATUS "Not adding preprocessor definitions to CrossWindowGraphics")
endif()

