# XInput Integration Research (2025)

## Source
- [Microsoft XInput Programming Guide](https://learn.microsoft.com/en-us/windows/win32/xinput/programming-guide) (2024-03-01)

## Key Points
- XInput is the Microsoft API for Xbox controller support on Windows.
- Use XInput for polling controller state, button presses, analog sticks, triggers, and vibration.
- Supports up to 4 controllers.
- Initialization can be implicit (first call) or explicit (see XINPUT_ON_GAMEINPUT_EXPLICIT_INITIALIZATION).
- For best performance, poll controllers once per frame/tick.
- Handle disconnects and hot-plug events gracefully.
- XInput is the standard for modern controller support on Windows and is recommended for all new projects.

## Agent-Ready Implementation

### 1. Setup
- Include in DLL project:
  ```cpp
  #include <Windows.h>
  #include <Xinput.h>
  #pragma comment(lib, "Xinput.lib")
  ```

### 2. Polling Loop Example
```cpp
void PollController() {
    for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(i, &state);
        if (result == ERROR_SUCCESS) {
            // Controller is connected
            WORD buttons = state.Gamepad.wButtons;
            SHORT lx = state.Gamepad.sThumbLX;
            SHORT ly = state.Gamepad.sThumbLY;
            // Map buttons/axes here
        } else if (result == ERROR_DEVICE_NOT_CONNECTED) {
            // Handle disconnect
        }
    }
}
```
- Call `PollController()` once per frame or in a dedicated thread.

### 3. Mapping Table Example
```json
{
  "A": "VK_RETURN",
  "B": "VK_ESCAPE",
  "DPadUp": "VK_UP",
  "DPadDown": "VK_DOWN",
  "LThumb": "WASD",
  "RThumb": "Mouse"
}
```
- Load mapping at DLL init; allow user remapping.

### 4. Error Handling
- If `XInputGetState` returns `ERROR_DEVICE_NOT_CONNECTED`, display warning or fallback to keyboard/mouse.
- Poll all 4 slots to support hot-plug.

### 5. Vibration Example
```cpp
XINPUT_VIBRATION vibration = {0};
vibration.wLeftMotorSpeed = 65535; // Max
vibration.wRightMotorSpeed = 65535; // Max
XInputSetState(0, &vibration);
```

### 6. References
- [Microsoft Docs: XInput](https://learn.microsoft.com/en-us/windows/win32/xinput/xinput-game-controller-apis-portal)
- See also [technical-specs.md](../plan/technical-specs.md) for integration steps.

---

For further code samples and advanced features, see the official Microsoft documentation.
