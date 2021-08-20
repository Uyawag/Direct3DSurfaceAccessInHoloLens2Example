#pragma once

#define NOMINMAX
#include <windows.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>

void __stdcall Direct3DSurfaceAccess(
	const winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface* d3dSurface,
	char* message,
	size_t messageLength
);
