# Controller UI Accessibility Guidelines (2025)

## Source
- [Game Accessibility Guidelines – Motor](https://gameaccessibilityguidelines.com/full-list/)

## Requirements
- **Full controller navigation:** All menus, dialogs, and UI elements must be accessible via D-pad, sticks, and buttons (no mouse/keyboard required).
- **Large hit targets:** All actionable UI elements must have a minimum size of 48x48 pixels (recommended by [Game Accessibility Guidelines](https://gameaccessibilityguidelines.com/full-list/)).
- **Readable fonts:** Use high-contrast text, minimum font size 14pt, scalable via config.
- **Visual feedback:** Always show clear focus highlight on the currently selected element. Use both color and shape.
- **Colorblind support:** Avoid using color as the only means of conveying information. Provide colorblind-friendly palettes and test with color filters.
- **Remapping:** Allow all controller buttons and axes to be remapped via config or in-game menu.
- **Toggle/hold options:** For repeated actions (e.g., sprint, targeting), support both toggle and hold modes.
- **Audio cues:** Provide optional audio feedback for navigation and selection.
- **Accessibility menu:** Add a dedicated menu for toggling accessibility features.

## Actionable Test Cases
1. **Navigate all menus using controller only.**
   - Criteria: No mouse/keyboard required; focus highlight always visible.
2. **All buttons and interactive elements are at least 48x48px.**
   - Criteria: Confirm via UI inspection or automated test.
3. **Text is readable and high-contrast.**
   - Criteria: Meets WCAG AA contrast ratio; user can scale font in config.
4. **Colorblind mode can be enabled.**
   - Criteria: UI remains fully usable in deuteranopia, protanopia, and tritanopia filters.
5. **All controls can be remapped.**
   - Criteria: User can assign any action to any button/axis.
6. **Toggle/hold options are available for all repeat actions.**
   - Criteria: User can choose preferred input mode in config.
7. **Audio cues can be enabled/disabled.**
   - Criteria: User can toggle in accessibility menu.

## Best Practices
- Test with a range of controllers and users with different abilities.
- Provide documentation and in-game help for accessibility features.
- Follow evolving accessibility standards and update regularly.

---

For more detailed guidelines, see the full list at GameAccessibilityGuidelines.com.
