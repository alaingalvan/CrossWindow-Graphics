#pragma once

#if !defined(XGFX_VULKAN) && !defined(XGFX_OPENGL) && !defined(XGFX_DIRECTX) && !defined(XGFX_METAL)
#define XGFX_VULKAN
#endif

#include "Graphics/Vulkan.h"
#include "Graphics/OpenGL.h"
#include "Graphics/DirectX12.h"
#include "Graphics/Metal.h"