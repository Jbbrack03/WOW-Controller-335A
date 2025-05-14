# Client Modding Guidelines

## Environment Setup
- Use a clean WoW 3.3.5a client (build 12340)
- Set up version control (git) for modded client files
- Recommended tools: Visual Studio, Ghidra/IDA Pro, x64dbg

## Modding Best Practices (2025)
- Prefer DLL injection for maintainability (vs. direct binary patching)
- Isolate controller code in a dedicated module
- Use Xinput for controller polling
- Avoid modifying core game logic unless necessary
- Document all changes and offsets
- Test on multiple hardware configurations

## Legal & Ethical Notice
- Modding is for personal/private server use only
- Do not distribute modified clients or copyrighted assets

## References
- [WoW Modding Communities: Modcraft, OwnedCore]
- [AzerothCore Wiki](https://github.com/azerothcore/wiki)

---

For input mapping and UI code, see the controller-support and UI/UX docs.
