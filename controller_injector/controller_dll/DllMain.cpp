// DllMain.cpp: Minimal DLL for injection and controller polling
#include <windows.h>
#include <Xinput.h>
#include <fstream>
#include <thread>
#include <atomic>

std::atomic<bool> running{true};

void PollController() {
    std::ofstream log("C:/temp/controller_log.txt", std::ios::app);
    while (running) {
        XINPUT_STATE state = {0};
        DWORD result = XInputGetState(0, &state);
        if (result == ERROR_SUCCESS) {
            log << "Controller connected. Buttons: " << state.Gamepad.wButtons << std::endl;
        } else {
            log << "Controller not detected." << std::endl;
        }
        log.flush();
        Sleep(1000);
    }
    log << "Polling thread exiting." << std::endl;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    static std::thread pollThread;
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        pollThread = std::thread(PollController);
        break;
    case DLL_PROCESS_DETACH:
        running = false;
        if (pollThread.joinable()) pollThread.join();
        break;
    }
    return TRUE;
}
