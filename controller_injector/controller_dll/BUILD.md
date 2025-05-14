# Building the Controller DLL

## Prerequisites
- Visual Studio 2019 or later
- Windows SDK
- XInput libraries (included in Windows SDK)

## Build Steps
1. Open Visual Studio, create a new DLL project.
2. Add `DllMain.cpp` to the project.
3. Link against `Xinput.lib`.
4. Build in Release mode.

## Output
- `controller_dll.dll` — ready for injection into Wow.exe
