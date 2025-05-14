// test_settings_overlay.cpp
// Demonstrates and tests a WoW-style settings overlay with controller-centric prompts and animation
// Uses Google Test framework and Direct3D9

#include <gtest/gtest.h>
#include "dx_overlay.h"
#ifdef _WIN32
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <vector>
#include <string>

// Helper: Minimal Direct3D9 device for offscreen rendering
typedef std::unique_ptr<IDirect3DDevice9, void(*)(IDirect3DDevice9*)> DevicePtr;
DevicePtr CreateTestD3DDevice(HWND hwnd) {
    IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d) return {nullptr, nullptr};
    D3DPRESENT_PARAMETERS pp = {};
    pp.Windowed = TRUE;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.hDeviceWindow = hwnd;
    IDirect3DDevice9* dev = nullptr;
    HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &dev);
    d3d->Release();
    return {dev, [](IDirect3DDevice9* d) { if (d) d->Release(); }};
}

// Test: Render WoW-style settings overlay with animated controller prompts
TEST(SettingsOverlayTest, RenderSettingsOverlayWithPrompts) {
    HWND hwnd = GetConsoleWindow();
    auto dev = CreateTestD3DDevice(hwnd);
    ASSERT_TRUE(dev != nullptr);
    dev->Clear(0, nullptr, D3DCLEAR_TARGET, 0x222244, 1.0f, 0);
    dev->BeginScene();
    // Overlay animation (mid fade-in)
    OverlayAnimState overlayAnim;
    overlayAnim.time = 0.6f;
    overlayAnim.entering = true;
    DrawOverlayBox(40, 40, 300, 180, &overlayAnim, dev.get());
    // Section title
    DrawTextLabel("Settings", 70, 60, OverlayColors::TEXT_GOLD, dev.get());
    // Option labels
    DrawTextLabel("Sound: On", 90, 100, OverlayColors::TEXT, dev.get());
    DrawTextLabel("Vibration: Off", 90, 130, OverlayColors::DISABLED, dev.get());
    DrawTextLabel("Back", 90, 170, OverlayColors::TEXT, dev.get());
    // Controller prompts (A=Select, B=Back, D-pad=Navigate)
    std::vector<std::pair<std::string, PromptAnimState>> prompts = {
        {"A", PromptAnimState{.time=0.4f, .active=true}},
        {"B", PromptAnimState{.time=0.2f, .active=false}},
        {"D-pad", PromptAnimState{.time=0.0f, .active=false}}
    };
    DrawControllerPrompts(prompts, 200, 200, 40, dev.get());
    // Smooth animated focus highlight transitioning from first to second option
    FocusTransitionState focusTrans;
    focusTrans.startX = 85; focusTrans.startY = 95; focusTrans.startW = 120; focusTrans.startH = 28; // "Sound: On"
    focusTrans.endX = 85; focusTrans.endY = 125; focusTrans.endW = 150; focusTrans.endH = 28; // "Vibration: Off"
    focusTrans.t = 0.5f; // Midway through transition
    focusTrans.animating = true;
    FocusAnimState focusAnim; focusAnim.time = 0.3f;
    DrawAnimatedFocusBorder(focusTrans, OverlayColors::FOCUS, dev.get(), &focusAnim);
    dev->EndScene();
    SUCCEED();
}
#endif

#ifndef _WIN32
TEST(SettingsOverlayTest, RenderSettingsOverlayWithPrompts) {
    SUCCEED();
}
#endif
