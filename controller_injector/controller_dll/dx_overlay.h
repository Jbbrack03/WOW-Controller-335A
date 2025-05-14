// dx_overlay.h
// Platform-specific overlay rendering abstraction for UI elements
#pragma once
#ifdef _WIN32
#include <d3d9.h>
#else
// No DirectX on non-Windows; stubs only
#endif
#include <string>
#include <cstdint>

// ---- Overlay UI Color Scheme ----
namespace OverlayColors {
    constexpr uint32_t BACKGROUND      = 0xEEDCCBAA; // parchment-like, semi-transparent
    constexpr uint32_t SHADOW         = 0x66000000; // soft drop shadow
    constexpr uint32_t BORDER_GOLD     = 0xFFBFA05A; // gold border (WoW-style)
    constexpr uint32_t BORDER_BRONZE   = 0xFF8C7853; // bronze border (alt)
    constexpr uint32_t FOCUS           = 0xFF66CCFF; // bright blue (controller focus)
    constexpr uint32_t FOCUS_ANIM      = 0xA066CCFF; // animated (pulsing) focus
    constexpr uint32_t FOCUS_GLOW      = 0x80FFFF99; // soft glow for focus
    constexpr uint32_t TEXT            = 0xFFFFFFFF; // white
    constexpr uint32_t TEXT_GOLD       = 0xFFFFD700; // gold for highlights
    constexpr uint32_t DISABLED        = 0xAA888888; // disabled/greyed
}

// ---- Overlay UI Config ----
namespace OverlayConfig {
    constexpr int PADDING = 8;
    constexpr int BORDER_THICKNESS = 2;
}

// ---- Animation State for Focus Border ----
struct FocusAnimState {
    float time; // time in seconds, for animation
    FocusAnimState() : time(0.0f) {}
};

// ---- Animation State for Overlay Transitions ----
struct OverlayAnimState {
    float time;    // time in seconds since transition started
    bool entering; // true if fade/slide in, false if out
    OverlayAnimState() : time(0.0f), entering(true) {}
};

#ifdef _WIN32
void DrawRect(int x, int y, int w, int h, unsigned int color, IDirect3DDevice9* dev);
void DrawShadowRect(int x, int y, int w, int h, int offset, unsigned int color, IDirect3DDevice9* dev);
void DrawTextLabel(const std::string& text, int x, int y, unsigned int color, IDirect3DDevice9* dev);
void DrawFocusBorder(int x, int y, int w, int h, unsigned int color, IDirect3DDevice9* dev, const FocusAnimState* anim = nullptr);
void DrawGoldBorder(int x, int y, int w, int h, int thickness, unsigned int color, IDirect3DDevice9* dev);
void DrawOverlayBox(int x, int y, int w, int h, const OverlayAnimState* anim, IDirect3DDevice9* dev);
// Animation state for controller prompt (e.g., glow or scale effect)
struct PromptAnimState {
    float time; // time in seconds since animation started
    bool active; // true if button is pressed/highlighted
    PromptAnimState() : time(0.0f), active(false) {}
};

void DrawControllerPrompt(const std::string& button, int x, int y, unsigned int color, IDirect3DDevice9* dev, const PromptAnimState* anim = nullptr);
// Helper: Draw multiple prompts (A, B, X, Y, D-pad, triggers)
void DrawControllerPrompts(const std::vector<std::pair<std::string, PromptAnimState>>& prompts, int x, int y, int spacing, IDirect3DDevice9* dev);

#else
// Stubs for Mac/Linux
inline void DrawRect(int, int, int, int, unsigned int, void*) {}
inline void DrawShadowRect(int, int, int, int, int, unsigned int, void*) {}
inline void DrawTextLabel(const std::string&, int, int, unsigned int, void*) {}
inline void DrawFocusBorder(int, int, int, int, unsigned int, void*, const void*) {}
inline void DrawGoldBorder(int, int, int, int, int, unsigned int, void*) {}
inline void DrawOverlayBox(int, int, int, int, const void*, void*) {}
inline void DrawControllerPrompt(const std::string&, int, int, unsigned int, void*) {}
#endif

// TODO: Add further extensibility for overlay themes/animations as needed.


// TODO: Add further extensibility for overlay themes/animations as needed.
