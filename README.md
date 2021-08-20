# Direct3DSurfaceAccessInHoloLens2Example

Example project for below question.

https://stackoverflow.com/questions/68841164/how-to-get-pixel-data-from-videomediaframe-direct3dsurface

## Usage

Use Unity 2019.4.28f1 and Visual Studio 2019.

### Build C++ unmanaged DLL

1. Visual Studio, open PluginProjects\Direct3DSurfaceAccess\Direct3DSurfaceAccess.sln and build.

   - Generate DLL and robocopy to Assets/Plugins/WSA/ARM/.

### Build Unity Project and deploy to HoloLens 2

1. Unity, File > Build Settings... > [Build]

2. Select output folder (e.g. `Build`).

3. Exports a Visual Studio UWP Project.

4. Visual Studio, open the output .sln and build Debug|ARM.

5. Deploy app to HoloLens 2 and run (Debug > Run Without Debugging).

   - HoloLens 2 waits attach for debugging.

6. Unity, Assets > Open C# Project (Open Visual Studio).

7. Visual Studio, open Assets/MyProject/Scripts/Direct3DSurfaceAccessHoloLens2.cs, and set brake point to line 76 (Call Direct3DSurfaceAccess function).

8. Attach to HoloLens 2 process.

9. Start HoloLens 2 that waiting.

   - Stop on break point.

10. Continue, crash in Direct3DSurfaceAccess.dll...
