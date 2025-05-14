# UI/UX for Controller Navigation

## Goals
- Full controller navigation from game launch to in-game
- Visual feedback for focus/selection
- Button prompts and tooltips for controller actions
- Accessibility: large hit targets, readable fonts, colorblind support

## Best Practices (2025)
- Use D-pad/left stick for navigation, A/B/X/Y for actions
- Highlight focused menu items
- Support both analog and digital navigation
- Allow toggling between controller and mouse modes
- Test on ROG Ally and standard Xbox controllers

## Implementation Notes
- Patch main menu and character select for controller navigation
- Add on-screen button hints
- Use configuration file or in-game menu for UI preferences

## Resources
- [ConsolePort UI inspiration](https://github.com/seblindfors/ConsolePort)
- [AzerothCore UI customization](https://github.com/azerothcore/wiki)

---

For technical implementation, see client-modding and controller-support docs.
