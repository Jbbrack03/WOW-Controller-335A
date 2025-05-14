// dx_overlay.cpp
// Platform-specific overlay rendering implementation
#include "dx_overlay.h"
#ifdef _WIN32
#include <d3d9.h>
#include <vector>
// Minimal Direct3D9 rectangle rendering for UI overlays
// For production: consider batching, state management, device loss handling, and font rendering

struct Vertex {
    float x, y, z, rhw;
    unsigned int color;
};

void DrawRect(int x, int y, int w, int h, unsigned int color, IDirect3DDevice9* dev) {
    if (!dev) return;
    Vertex verts[] = {
        {float(x),     float(y),     0.0f, 1.0f, color},
        {float(x+w),   float(y),     0.0f, 1.0f, color},
        {float(x),     float(y+h),   0.0f, 1.0f, color},
        {float(x+w),   float(y+h),   0.0f, 1.0f, color},
    };
    dev->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
    dev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, verts, sizeof(Vertex));
    // Note: In production, save/restore device state and batch calls for performance
}

#include <d3dx9.h>

void DrawTextLabel(const std::string& text, int x, int y, unsigned int color, IDirect3DDevice9* dev) {
    if (!dev) return;
    static ID3DXFont* font = nullptr;
    if (!font) {
        // Create font (Arial, 18pt, bold)
        D3DXCreateFont(dev, 18, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &font);
    }
    if (font) {
        RECT rect = { x, y, x + 1000, y + 40 };
        std::wstring wtext(text.begin(), text.end());
        font->DrawTextW(NULL, wtext.c_str(), -1, &rect, DT_LEFT | DT_TOP, color);
    }
    // Note: In production, handle device loss/reset and font cleanup.
}

void DrawFocusBorder(int x, int y, int w, int h, unsigned int color, IDirect3DDevice9* dev, const FocusAnimState* anim) {
    // Animated pulsing border: modulate alpha with time if anim provided
    unsigned int borderColor = color;
    if (anim) {
        float pulse = 0.5f + 0.5f * sinf(anim->time * 3.0f); // 0..1
        unsigned int alpha = static_cast<unsigned int>(0xA0 + 0x5F * pulse); // 0xA0-0xFF
        borderColor = (borderColor & 0x00FFFFFF) | (alpha << 24);
    }
    DrawRect(x - OverlayConfig::BORDER_THICKNESS, y - OverlayConfig::BORDER_THICKNESS,
             w + 2 * OverlayConfig::BORDER_THICKNESS, h + 2 * OverlayConfig::BORDER_THICKNESS,
             borderColor, dev);
}

// ---- WoW-style Drop Shadow ----
void DrawShadowRect(int x, int y, int w, int h, int offset, unsigned int color, IDirect3DDevice9* dev) {
    // Draws a shadow rectangle offset from the main overlay
    DrawRect(x + offset, y + offset, w, h, color, dev);
}

// ---- WoW-style Gold/Bronze Border ----
void DrawGoldBorder(int x, int y, int w, int h, int thickness, unsigned int color, IDirect3DDevice9* dev) {
    // Draws a border of the specified thickness
    for (int i = 0; i < thickness; ++i) {
        DrawRect(x - i, y - i, w + 2 * i, h + 2 * i, color, dev);
    }
}

// ---- Animated Overlay Box (fade/slide in/out) ----
void DrawOverlayBox(int x, int y, int w, int h, const OverlayAnimState* anim, IDirect3DDevice9* dev) {
    // Fade and slide animation
    float alpha = 1.0f;
    int slideOffset = 0;
    if (anim) {
        float t = anim->time;
        float fade = anim->entering ? (t < 1.0f ? t : 1.0f) : (t < 1.0f ? 1.0f - t : 0.0f);
        alpha = fade;
        slideOffset = static_cast<int>((1.0f - fade) * 30.0f); // Slide from right
    }
    // Compose alpha with background color
    unsigned int bg = (OverlayColors::BACKGROUND & 0x00FFFFFF) | (static_cast<unsigned int>(alpha * ((OverlayColors::BACKGROUND >> 24) & 0xFF)) << 24);
    unsigned int shadow = (OverlayColors::SHADOW & 0x00FFFFFF) | (static_cast<unsigned int>(alpha * ((OverlayColors::SHADOW >> 24) & 0xFF)) << 24);
    // Draw drop shadow
    DrawShadowRect(x + slideOffset, y + slideOffset, w, h, 6, shadow, dev);
    // Draw background
    DrawRect(x + slideOffset, y + slideOffset, w, h, bg, dev);
    // Draw gold border
    DrawGoldBorder(x + slideOffset, y + slideOffset, w, h, OverlayConfig::BORDER_THICKNESS, OverlayColors::BORDER_GOLD, dev);
}

// ---- Controller Prompt (stub: renders button text) ----
void DrawControllerPrompt(const std::string& button, int x, int y, unsigned int color, IDirect3DDevice9* dev, const PromptAnimState* anim) {
    // Animate prompt: scale up and glow if active/pressed
    float scale = 1.0f;
    unsigned int promptColor = color;
    if (anim && anim->active) {
        scale = 1.1f + 0.05f * sinf(anim->time * 6.0f); // pulse
        unsigned int alpha = 0xFF;
        // Add a soft glow effect by blending with FOCUS_GLOW
        promptColor = (promptColor & 0x00FFFFFF) | (alpha << 24);
    }
    // Simulate scale by adjusting position (for text)
    int sx = static_cast<int>(x - 8 * (scale - 1.0f));
    int sy = static_cast<int>(y - 8 * (scale - 1.0f));
    // In production, replace with icon rendering
    DrawTextLabel("[" + button + "]", sx, sy, promptColor, dev);
    // Optionally, draw a glow/halo (could use DrawRect or DrawFocusBorder for more effect)
    if (anim && anim->active) {
        DrawFocusBorder(sx - 2, sy - 2, 32, 32, OverlayColors::FOCUS_GLOW, dev, nullptr);
    }
}

void DrawControllerPrompts(const std::vector<std::pair<std::string, PromptAnimState>>& prompts, int x, int y, int spacing, IDirect3DDevice9* dev) {
    int cx = x;
    for (const auto& p : prompts) {
        DrawControllerPrompt(p.first, cx, y, OverlayColors::FOCUS, dev, &p.second);
        cx += spacing;
    }
}

#endif
