# Implementation Roadmap (Agent-Ready)

## Phases & Milestones

1. **Research & Planning**
   - Gather requirements, research APIs and client modding techniques ([xinput-integration.md](../research/xinput-integration.md), [controller-ui-accessibility.md](../research/controller-ui-accessibility.md))
   - Document findings in /docs/research
   - Identify memory offsets and patching strategies ([client-modding.md](../client-modding.md))

2. **Prototyping**
   - DLL injector proof-of-concept ([tasks.md](tasks.md#1-dll-injector-proof-of-concept))
   - XInput polling and event mapping ([xinput-integration.md](../research/xinput-integration.md))
   - Evaluate feasibility and performance on target hardware

3. **Core Integration**
   - Integrate input into client event loop ([technical-specs.md](technical-specs.md#1-input-handling))
   - Implement error handling and hot-plug support
   - Patch main menu and character select for controller navigation ([tasks.md](tasks.md#4-patch-main-menu-for-controller-navigation))

4. **UI/UX Enhancements**
   - Add visual feedback, button prompts, accessibility features ([controller-ui-accessibility.md](../research/controller-ui-accessibility.md))
   - Implement in-game configuration menus ([technical-specs.md](technical-specs.md#4-configuration))

5. **Testing & QA**
   - Comprehensive hardware/OS test matrix ([testing-plan.md](testing-plan.md#test-matrix))
   - Regression and edge-case testing ([testing-plan.md](testing-plan.md#test-cases--acceptance-criteria))

6. **Release & Maintenance**
   - Prepare release builds and documentation ([contributing.md](../contributing.md), [onboarding.md](onboarding.md))
   - Track issues, gather feedback, iterate ([changelog.md](changelog.md))

## Deliverables
- Native controller support in WoW 3.3.5a client
- Controller-friendly menu and in-game UI
- Agent/developer-ready documentation for users and contributors

---

**Cross-References:**
- Technical specs: [technical-specs.md](technical-specs.md)
- Engineering tasks: [tasks.md](tasks.md)
- Testing plan: [testing-plan.md](testing-plan.md)
- Accessibility: [controller-ui-accessibility.md](../research/controller-ui-accessibility.md)
- XInput integration: [xinput-integration.md](../research/xinput-integration.md)
- Risk assessment: [risk-assessment.md](risk-assessment.md)

For detailed, step-by-step implementation, see [tasks.md](tasks.md).
