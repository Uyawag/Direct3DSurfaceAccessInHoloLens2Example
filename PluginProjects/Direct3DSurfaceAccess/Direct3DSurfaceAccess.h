#pragma once

#define NOMINMAX
#include <windows.h>

void __stdcall Direct3DSurfaceAccess(
	::IUnknown* d3dSurfacePtr,
	char* message,
	size_t messageLength
);
