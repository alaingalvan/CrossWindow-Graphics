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
set(XGFX_PROTOCOL AUTO CACHE STRING "A more specific platform selector to choose from, choose the exact graphics protocol to use, defaults to VULKAN, can be VULKAN, OPENGL, DIRECTX12, or METAL.")
set_property(
    CACHE
    XGFX_PROTOCOL PROPERTY
    STRINGS VULKAN OPENGL DIRECTX12 METAL
)
target_compile_definitions(CrossWindowGraphics INTERFACE XGFX_${XGFX_PROTOCOL}=1)