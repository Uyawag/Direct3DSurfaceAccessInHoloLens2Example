# Direct3DSurfaceAccessInHoloLens2Example

Example project for below question.

https://stackoverflow.com/questions/68841164/how-to-get-pixel-data-from-videomediaframe-direct3dsurface

## Usage

Use Unity 2019.4.28f1 and Visual Studio 2019.

### Build C++ unmanaged DLL

1. Visual Studio, open PluginProjects\Direct3DSurfaceAccess\Direct3DSurfaceAccess.sln and build.

   - Generate DLL and robocopy to Assets/Plugins/WSA/ARM/.

### Build Unity Project and deploy to HoloLens 2

1. Unity, open project folder.

2. If MRTK window opened, select "Always skip setup".

3. If scene in Hierarchy view is "Untitled", open Assets/MyProject/Scenes/SampleScene.

4. File > Build Settings...

5. Switch platform to "Universal Windows Platform" with below settings.

   - Target Device: HoloLens
   - Architecture: ARM
   - Development Build: Checked
   - Script Debugging: Checked
   - Wait For Managed Debugger: Checked

6. Build and select output folder (e.g. `Build`).

   - Exports a Visual Studio UWP Project.

7. Visual Studio, open the output .sln and build Debug|ARM.

8. Deploy app to HoloLens 2 and run (Debug > Run Without Debugging).

   - HoloLens 2 waits attach for debugging.

9. Unity, Assets > Open C# Project (Open Visual Studio).

10. Visual Studio, open Assets/MyProject/Scripts/Direct3DSurfaceAccessHoloLens2.cs, and set brake point to line 76 (Call Direct3DSurfaceAccess function).

11. Attach to HoloLens 2 process.

12. Start HoloLens 2 that waiting.

    - Stop on break point.

13. Continue, crash in Direct3DSurfaceAccess.dll...
