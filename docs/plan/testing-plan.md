# Testing & Validation Plan (Agent-Ready)

## Test Matrix
| Platform     | Controller Models           | OS Version         |
|--------------|----------------------------|--------------------|
| ROG Ally     | Built-in Xbox              | Windows 11 23H2+   |
| Desktop PC   | Xbox 360, Xbox One, Elite  | Windows 10/11      |
| Desktop PC   | DualShock 4 (w/ wrapper)   | Windows 10/11      |
| (Optional)   | Any XInput-compatible      | Linux (Wine/Proton)|

## Test Cases & Acceptance Criteria

### 1. Game Launch & Main Menu
- **Test:** Launch game; navigate main menu with D-pad/left stick.
- **Criteria:** All menu items accessible; A = select, B = back, focus highlight visible.

### 2. Controller Hot-Plug/Disconnect
- **Test:** Connect/disconnect controller at any time.
- **Criteria:** Game detects and adapts without crash; fallback to keyboard/mouse.

### 3. In-Game Movement, Camera, Combat
- **Test:** Move character, control camera, perform actions with controller.
- **Criteria:** No lag; all mapped actions work; no input loss.

### 4. UI Navigation (Menus, Settings, Char Select)
- **Test:** Navigate all UI screens using controller only.
- **Criteria:** All screens accessible; no mouse/keyboard required; button prompts visible.

### 5. Fallback to Keyboard/Mouse
- **Test:** Use keyboard/mouse at any time.
- **Criteria:** No input lockout; both input methods work seamlessly.

### 6. Edge Cases
- **Test:**
  - Multiple controllers connected
  - System sleep/resume
  - Controller battery low/disconnect
- **Criteria:** No crash; input restored on resume/reconnect.

### 7. Accessibility
- **Test:**
  - Large hit targets
  - Readable fonts
  - Colorblind mode enabled
  - Remapping and sensitivity adjustment
- **Criteria:** Passes all guidelines in [controller-ui-accessibility.md](../research/controller-ui-accessibility.md).

## Bug Reporting
- Use GitHub Issues for tracking
- Include hardware, OS, controller model, and reproduction steps
- Prioritize accessibility/usability bugs

---

For release notes, see changelog.md.
