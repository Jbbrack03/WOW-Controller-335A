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

#endif
