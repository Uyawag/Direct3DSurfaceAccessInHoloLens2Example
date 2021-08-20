using Cysharp.Threading.Tasks;
using System;
using System.Text;
using System.Linq;
using System.Runtime.InteropServices;
using UnityEngine;

#if ENABLE_WINMD_SUPPORT
using Windows.Media.Capture;
using Windows.Media.Capture.Frames;
#endif

public class Direct3DSurfaceAccessHoloLens2 : MonoBehaviour {
#if ENABLE_WINMD_SUPPORT
	private MediaCapture m_mediaCapture = null!;

	async void Start() {
		// Initialize MediaCapture for HoloLens 2.

		UnityEngine.WSA.Application.InvokeOnUIThread(async () => {
			try {
				m_mediaCapture = new();

				var source = (await MediaFrameSourceGroup.FindAllAsync()).Select(g => new {
					Group = g,
					Info = g.SourceInfos.FirstOrDefault(info => info.MediaStreamType == MediaStreamType.VideoRecord
						&& info.SourceKind == MediaFrameSourceKind.Color)
				}).FirstOrDefault(s => s.Info != null);
				if (source == null) {
					throw new Exception("Media frame source not found.");
				}

				var settings = new MediaCaptureInitializationSettings() {
					SourceGroup = source.Group,
					SharingMode = MediaCaptureSharingMode.SharedReadOnly,
					MemoryPreference = MediaCaptureMemoryPreference.Auto,
					StreamingCaptureMode = StreamingCaptureMode.AudioAndVideo
				};

				await m_mediaCapture.InitializeAsync(settings);

				var frameSource = m_mediaCapture.FrameSources[source.Info.Id];
				var preferredFormat = frameSource.SupportedFormats.FirstOrDefault(format => 1080 <= format.VideoFormat.Width);
				if (preferredFormat == null) {
					throw new Exception("Frame format not found.");
				}
				await frameSource.SetFormatAsync(preferredFormat);

				var mediaFrameReader = await m_mediaCapture.CreateFrameReaderAsync(frameSource, preferredFormat.Subtype);

				if (preferredFormat.Subtype == "NV12") {
					mediaFrameReader.FrameArrived += Nv12FrameArrived;
				}

				await mediaFrameReader.StartAsync();
			} catch (Exception error) {
				Debug.LogException(error);
			}
		}, waitUntilDone: true);
	}

	[DllImport("Direct3DSurfaceAccess")]
	private static extern void Direct3DSurfaceAccess(
		[MarshalAs(UnmanagedType.Interface)] Windows.Graphics.DirectX.Direct3D11.IDirect3DSurface d3dSurface,
		[Out] StringBuilder errorMessage,
		int errorMessageLength
	);

	// MediaFrameReader.FrameArrived event.
	private void Nv12FrameArrived(MediaFrameReader sender, MediaFrameArrivedEventArgs args) {
		using var mediaFrameReference = sender.TryAcquireLatestFrame();

		// I could't find how to get pixel data from IDirect3DSurface using C# only.
		// Use C++/WinRT for access IDirect3DSurface as below.
		var messageBuilder = new StringBuilder(1024);
		Direct3DSurfaceAccess(
			mediaFrameReference.VideoMediaFrame.Direct3DSurface,
			messageBuilder,
			messageBuilder.Capacity
		);

		var message = messageBuilder.ToString();
	}
#endif
}
