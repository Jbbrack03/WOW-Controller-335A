# AzerothCore Integration

## Overview
AzerothCore is a modern, modular, open-source WoW server emulator for 3.3.5a. This project is designed for seamless compatibility with AzerothCore.

## Best Practices (2025)
- Use the latest AzerothCore release: https://github.com/azerothcore/azerothcore-wotlk
- Keep server and client at patch 3.3.5a (build 12340)
- Use AzerothCore modules for custom features, not core hacks
- Test all controller features on both Windows and Linux hosts
- Monitor the [AzerothCore Wiki](https://github.com/azerothcore/wiki) for updates

## Client-Server Considerations
- Controller support is client-side; no server changes required
- Ensure no anti-cheat modules block client DLL injection (if used)
- For cross-platform play, test controller features on all OSes supported by AzerothCore

## Troubleshooting
- If you encounter input or UI issues, check AzerothCore logs and client logs
- Report compatibility issues to both this project and AzerothCore maintainers

---

For advanced integration or module development, see the AzerothCore Wiki and community forums.
