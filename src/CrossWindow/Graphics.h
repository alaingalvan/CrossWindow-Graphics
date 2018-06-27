#pragma once

#if !defined(XGFX_VULKAN) && !defined(XGFX_OPENGL) && !defined(XGFX_DIRECTX12) && !defined(XGFX_DIRECTX11) && !defined(XGFX_METAL)
#error "Define either XGFX_VULKAN, XGFX_OPENGL, XGFX_DIRECTX12, XGFX_DIRECTX11, and/or XGFX_METAL before #include \"CrossWindow/Graphics.h\""
#endif

#include "Graphics/Vulkan.h"
#include "Graphics/OpenGL.h"
#include "Graphics/DirectX12.h"
#include "Graphics/DirectX11.h"
#include "Graphics/Metal.h"