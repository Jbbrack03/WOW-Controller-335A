# Task Breakdown (Agent-Ready)

## Recent Progress (2025-05-14)
- Implemented full cross-platform rendering abstraction (`dx_overlay`) for all UI elements.
- DirectX 9 overlay rendering (rectangles, text, focus highlights) now functional for Windows builds.
- All non-graphical, platform-agnostic tests pass on Mac using stubs.
- Documentation and build instructions updated for new rendering architecture.
- Accessibility features are not required for this project and have not been implemented.

## Next Engineering Steps
- Further UI/UX polish (visual and interaction improvements, not accessibility-specific).
  - Review overlay color schemes and highlight consistency.
  - Implement smoother focus transitions (basic animation).
  - Refine overlay positioning (padding/margin review).
  - Ensure code structure allows for easy future customization.
- Integration/system-level graphical tests.
  - Scaffold graphical test for overlay rendering output (Windows).
  - Integrate screenshot/pixel-diff comparison to baseline images.
  - Ensure Mac stub builds pass all non-graphical tests in CI/CD.
- Additional graphical features or menu screens as needed.
  - Implement overlay animation (fade/slide transitions).
  - Add new menu screens or overlays as required by UX review.
  - Review and refactor code for maintainability and extensibility.

## Engineering Tasks (with Details)

### 1. DLL Injector Proof-of-Concept
- **Objective:** Inject a custom DLL into WoW 3.3.5a client process (Wow.exe).
- **Steps:**
  1. Clone or build an open-source injector (e.g., [GH Injector](https://github.com/therealdreg/ghinjector)).
  2. Create a minimal DLL with `DllMain`, log to file on attach.
  3. Inject DLL into running Wow.exe, confirm log output.
- **Acceptance Criteria:** Log file confirms successful injection.
- **References:** [WoWHook](https://github.com/NightQuest/WoWHook)

### 2. XInput Polling and Event Mapping
- **Objective:** Poll Xbox controller state and map to virtual input.
- **Steps:**
  1. In DLL, include `<Xinput.h>`, link `Xinput.lib`.
  2. Implement polling thread or hook game loop.
  3. Use `XInputGetState()` to poll controller.
  4. Map buttons/axes to virtual keys/mouse using `SendInput` or direct memory patch.
- **Acceptance Criteria:** Button presses move character or trigger menu actions.
- **References:** [XInput Integration Research](../research/xinput-integration.md)

### 3. Integrate Input into Client Event Loop
- **Objective:** Ensure controller input is processed each frame.
- **Steps:**
  1. Identify main loop or DirectX Present function (e.g., 0x004A1B20).
  2. Hook using MinHook or similar.
  3. Call input polling and event mapping in the hook.
- **Acceptance Criteria:** No input lag; controller input always processed.

### 4. Patch Main Menu for Controller Navigation
- **Objective:** Allow D-pad/left stick to move menu selection.
- **Steps:**
  1. Identify menu navigation functions (static analysis with Ghidra/IDA).
  2. Patch/hook to intercept navigation and selection logic.
  3. Map A/B buttons to Enter/Esc.
- **Acceptance Criteria:** Full menu navigation via controller.

### 5. Patch Character Select for Controller Navigation
- **Objective:** Enable controller navigation in character select screen.
- **Steps:**
  1. Identify character select UI logic.
  2. Patch/hook to allow left/right to change character, A to select, B to back.
- **Acceptance Criteria:** Character can be selected and entered with controller only.

### 6. Add Button Prompts and Focus Highlights
- **Objective:** Display visual feedback for focused menu items and button prompts.
- **Steps:**
  1. Patch rendering function to draw overlays or textures.
  2. Use DirectX hooks for custom drawing if needed.
- **Acceptance Criteria:** User sees clear focus and button hints.

### 7. Implement Configuration System
- **Objective:** Allow remapping and settings persistence.
- **Steps:**
  1. Define config file format (JSON, INI).
  2. Load config at DLL init; reload on file change.
  3. Provide in-game or external UI for mapping.
- **Acceptance Criteria:** User can remap buttons and save preferences.

### 8. Add Accessibility Features
- **Objective:** Meet accessibility guidelines for controller navigation.
- **Steps:**
  1. Implement large hit targets, readable fonts, colorblind modes.
  2. Allow toggle/hold options for actions.
- **Acceptance Criteria:** Passes accessibility test cases in [controller-ui-accessibility.md](../research/controller-ui-accessibility.md).

### 9. Test on All Supported Hardware/OS
- **Objective:** Ensure compatibility and stability.
- **Steps:**
  1. Test on Windows 11, ROG Ally, Xbox controllers.
  2. Log and resolve issues for each platform.
- **Acceptance Criteria:** All test cases in [testing-plan.md](testing-plan.md) pass.

### 10. Write User and Developer Documentation
- **Objective:** Provide clear usage and contribution guides.
- **Steps:**
  1. Update /docs and /docs/plan as features are implemented.
  2. Add code comments, usage examples, and troubleshooting.
- **Acceptance Criteria:** Docs are up to date and agent/developer-ready.

## Usage
- Track progress by checking off tasks.
- Assign owners and due dates as needed.

---

For risk analysis, see risk-assessment.md.
