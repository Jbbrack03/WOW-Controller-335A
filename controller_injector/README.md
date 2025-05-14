# Controller Injector Module (Phase 1)

This module provides DLL injection and XInput controller integration for WoW 3.3.5a as part of ConsolePortLK.

## Structure
- `injector/` — DLL injector source or integration
- `controller_dll/` — DLL project for controller input
- `test/` — Scripts for validation

## Phase 1 Features
- DLL injection proof-of-concept
- XInput polling and event mapping
- Input integration with client event loop

## Building & Usage
See `controller_dll/BUILD.md` and `injector/BUILD.md` for instructions.

## References
- [tasks.md](../../docs/plan/tasks.md)
- [technical-specs.md](../../docs/plan/technical-specs.md)
- [xinput-integration.md](../../docs/research/xinput-integration.md)
