#include "pch.h"
#include "Direct3DSurfaceAccess.h"

void __stdcall Direct3DSurfaceAccess(
	::IUnknown* d3dSurfacePtr,
	char* message,
	size_t messageLength
) {
	try {
		HRESULT hr;

		winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface d3dSurface{ nullptr };
		hr = d3dSurfacePtr->QueryInterface(winrt::guid_of<decltype(d3dSurface)>(), winrt::put_abi(d3dSurface));
		if (FAILED(hr)) {
			::sprintf_s(message, messageLength, "d3dSurfacePtr->QueryInterface failed. hr: %08x", hr);
			return;
		}

		winrt::com_ptr<::Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess> dxgiInterfaceAccess;
		if (!d3dSurface.try_as(dxgiInterfaceAccess)) {
			::sprintf_s(message, messageLength, "d3dSurface->try_as failed.");
			return;
		}

		// Call other d3dSurface method as a test.
		//winrt::Windows::Graphics::DirectX::Direct3D11::Direct3DSurfaceDescription desc = d3dSurface.Description();
			// -> No problem.

		winrt::com_ptr<::IDXGISurface> nativeSurface;
		hr = dxgiInterfaceAccess->GetInterface(IID_PPV_ARGS(nativeSurface.put()));
		if (FAILED(hr)) {
			::sprintf_s(message, messageLength, "dxgiInterfaceAccess->GetInterface failed. hr: %08x", hr);
			return;
		}

		::DXGI_MAPPED_RECT rect;
		hr = nativeSurface->Map(&rect, DXGI_MAP_READ | DXGI_MAP_DISCARD);
		if (FAILED(hr)) {
			// Returns E_INVALIDARG when 2nd arg is "DXGI_MAP_READ" or "DXGI_MAP_READ | DXGI_MAP_DISCARD".
			// Should research.
			::sprintf_s(message, messageLength, "nativeSurface->Map failed. hr: %08x", hr);
			return;
		}

		const BYTE* pixels = rect.pBits; // Read pixel data from the pointer.

		hr = nativeSurface->Unmap();
		if (FAILED(hr)) {
			::sprintf_s(message, messageLength, "nativeSurface->Unmap failed. hr: %08x", hr);
			return;
		}
	} catch (...) {
		::sprintf_s(message, messageLength, "Caught any exception.");
		return;
	}

	::sprintf_s(message, messageLength, "Succeeded!");
}
