# Technical Specifications (Agent-Ready)

## 1. Input Handling
- **API:** Use Microsoft XInput (see [XInput Programming Guide](https://learn.microsoft.com/en-us/windows/win32/xinput/programming-guide))
- **Initialization:**
  - Include `#include <Xinput.h>` in DLL project.
  - Link against `Xinput.lib`.
- **Polling Loop:**
  - In DLL, create a polling thread or hook into the client’s main loop (e.g., via DirectX Present or game tick function).
  - Example code:
    ```cpp
    XINPUT_STATE state;
    DWORD dwResult = XInputGetState(0, &state);
    if (dwResult == ERROR_SUCCESS) {
      // Controller is connected
      // state.Gamepad.wButtons, state.Gamepad.sThumbLX, etc.
    }
    ```
- **Mapping:**
  - Map `XINPUT_GAMEPAD_A` to VK_RETURN (Enter), `XINPUT_GAMEPAD_B` to VK_ESCAPE, sticks to WASD/mouse via SendInput or direct memory patch.
  - Provide mapping table in config file (JSON, INI, or XML).
- **Error Handling:**
  - If `XInputGetState` returns `ERROR_DEVICE_NOT_CONNECTED`, display in-game warning or fallback to keyboard/mouse.
- **Hot-Plug:**
  - Poll all 4 controller slots; detect new connections/disconnects every second.

## 2. Client Patching / DLL Injection
- **Injection:**
  - Use open-source injector (e.g., [GH Injector](https://github.com/therealdreg/ghinjector) or custom).
  - DLL entry point: set up hooks and input polling.
- **Function Hooking:**
  - For menu navigation, hook DirectX Present or WoW’s main window message loop (commonly at address 0x004A1B20 for 3.3.5a, verify with Ghidra/IDA Pro).
  - Use [MinHook](https://github.com/TsudaKageyu/minhook) or similar library for function detouring.
- **Memory Offsets:**
  - Document all patched addresses. Example:
    - Main menu navigation: 0x004A1B20
    - Character select navigation: 0x004B2C40
    - (Offsets must be confirmed for your client build)
- **Compatibility:**
  - Ensure no anti-cheat is running. Test with AzerothCore 3.3.5a client (build 12340).

## 3. UI/UX Changes
- **Menu Navigation:**
  - Intercept menu navigation functions to allow D-pad/left stick movement between menu items.
  - Highlight focused item (patch rendering function, e.g., CEGUI or WoW’s custom UI code).
  - Add button prompts by overlaying textures or drawing with DirectX hooks.
- **Accessibility:**
  - Large hit targets, readable fonts, colorblind support (see [Game Accessibility Guidelines](https://gameaccessibilityguidelines.com/full-list/)).
  - Support remapping and sensitivity adjustment in config.
- **In-Game Config:**
  - Add a config menu (patch in-game UI or provide external config file). Allow remapping and saving preferences.

## 4. Configuration
- **Config File:**
  - Format: `controller-config.json` (example structure below)
    ```json
    {
      "A": "VK_RETURN",
      "B": "VK_ESCAPE",
      "LThumb": "WASD",
      "RThumb": "Mouse"
    }
    ```
  - Load config at DLL initialization; reload on file change if possible.
- **Persistence:**
  - Save user settings to config file or registry.

## 5. Compatibility
- **Tested Platforms:**
  - Windows 11, ROG Ally, Xbox 360/One/Elite controllers (XInput)
- **Known Issues:**
  - Non-XInput controllers require third-party wrappers.
  - Windows Defender may flag DLL injection (add exclusion or sign DLL).

---

For step-by-step implementation and code samples, see tasks.md and research/xinput-integration.md.
