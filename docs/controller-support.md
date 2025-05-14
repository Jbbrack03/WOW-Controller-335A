# Controller Support Best Practices

## Supported Controllers
- Xbox 360, Xbox One, Xbox Elite (Xinput)
- ROG Ally built-in controller (Xinput)
- DualShock 4 (with Xinput wrapper)

## 2025 Best Practices
- Use native Xinput APIs for polling controller state
- Provide in-game configuration for button mapping and sensitivity
- Support hot-plugging and disconnect/reconnect events
- Offer visual feedback for active controller profile
- Allow fallback to keyboard/mouse at any time
- Document tested controllers and known quirks

## Implementation Notes
- Use a DLL injector or patch client binary for input hooks
- Map controller input to in-game actions (WASD, camera, menu, etc.)
- Avoid hardcoding; support config files or in-game remapping
- Log input events for debugging

## Resources
- [Microsoft Xinput Docs](https://learn.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput)
- [ConsolePort (modern)](https://github.com/seblindfors/ConsolePort)

---

For controller mapping code and advanced usage, see the client-modding and UI/UX docs.
