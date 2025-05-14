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
    constexpr uint32_t BACKGROUND   = 0xAA222244; // semi-transparent dark blue
    constexpr uint32_t FOCUS        = 0xFF66CCFF; // bright blue
    constexpr uint32_t FOCUS_ANIM   = 0xA066CCFF; // animated (pulsing) focus
    constexpr uint32_t TEXT         = 0xFFFFFFFF; // white
    constexpr uint32_t BORDER       = 0xFF333366; // dark border
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

#ifdef _WIN32
void DrawRect(int x, int y, int w, int h, unsigned int color, IDirect3DDevice9* dev);
void DrawTextLabel(const std::string& text, int x, int y, unsigned int color, IDirect3DDevice9* dev);
void DrawFocusBorder(int x, int y, int w, int h, unsigned int color, IDirect3DDevice9* dev, const FocusAnimState* anim = nullptr);
#else
// Stubs for Mac/Linux
inline void DrawRect(int, int, int, int, unsigned int, void*) {}
inline void DrawTextLabel(const std::string&, int, int, unsigned int, void*) {}
inline void DrawFocusBorder(int, int, int, int, unsigned int, void*, const void*) {}
#endif

// TODO: Add further extensibility for overlay themes/animations as needed.
