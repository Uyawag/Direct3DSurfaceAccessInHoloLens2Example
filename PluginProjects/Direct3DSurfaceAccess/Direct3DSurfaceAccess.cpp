#include "pch.h"
#include "Direct3DSurfaceAccess.h"

void __stdcall Direct3DSurfaceAccess(
	const winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface* d3dSurface,
	char* message,
	size_t messageLength
) {
	// Here, confirmed that d3dSurface is not null.

	try {
		// Issue is here.

		winrt::com_ptr<::Windows::Graphics::DirectX::Direct3D11::IDirect3DDxgiInterfaceAccess> dxgiInterfaceAccess;
		if (!d3dSurface->try_as(dxgiInterfaceAccess)) {
			// App crashes on d3dSurface->try_as.
			::sprintf_s(message, messageLength, "d3dSurface->try_as failed.");
			return;
		}

		// Call other d3dSurface method as a test.
		winrt::Windows::Graphics::DirectX::Direct3D11::Direct3DSurfaceDescription desc = d3dSurface->Description();
			// Same above. App crashes on d3dSurface->Description.

		// Unreachable to here...
		// When succeeded to get the IDirect3DDxgiInterfaceAccess, read pixel data by below code.

		HRESULT hr;

		winrt::com_ptr<::IDXGISurface> nativeSurface;
		hr = dxgiInterfaceAccess->GetInterface(IID_PPV_ARGS(nativeSurface.put()));
		if (FAILED(hr)) {
			::sprintf_s(message, messageLength, "dxgiInterfaceAccess->GetInterface failed. hr: %08x", hr);
			return;
		}

		::DXGI_MAPPED_RECT rect;
		hr = nativeSurface->Map(&rect, DXGI_MAP_READ);
		if (FAILED(hr)) {
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

		// Can't catch any exceptions.
		// App freezes and downs on HoloLens 2.
	}

	::sprintf_s(message, messageLength, "Succeeded!");
}
