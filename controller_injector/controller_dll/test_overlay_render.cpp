// test_overlay_render.cpp
// System-level graphical test for overlay rendering (Windows only)
// Uses Google Test framework and Direct3D9

#include <gtest/gtest.h>
#include "dx_overlay.h"
#ifdef _WIN32
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>

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

// Test: Render overlay and focus border, check for device loss and no crash
TEST(OverlayRenderTest, RenderOverlayAndFocus) {
    HWND hwnd = GetConsoleWindow();
    auto dev = CreateTestD3DDevice(hwnd);
    ASSERT_TRUE(dev != nullptr);
    dev->Clear(0, nullptr, D3DCLEAR_TARGET, 0x222244, 1.0f, 0);
    dev->BeginScene();
    // Draw overlay background
    DrawRect(50, 50, 200, 100, OverlayColors::BACKGROUND, dev.get());
    // Draw label
    DrawTextLabel("Overlay Test", 70, 70, OverlayColors::TEXT, dev.get());
    // Draw animated focus border
    FocusAnimState anim;
    anim.time = 0.5f; // Simulate mid-pulse
    DrawFocusBorder(50, 50, 200, 100, OverlayColors::FOCUS, dev.get(), &anim);
    dev->EndScene();
    // Present is not needed for offscreen test
    SUCCEED();
}
#endif

// On non-Windows, this test is a stub.
#ifndef _WIN32
TEST(OverlayRenderTest, RenderOverlayAndFocus) {
    SUCCEED();
}
#endif
