#include <iostream>

template <typename T>
inline void print(T f) {
    std::cout << f;
}

template <typename First, typename... Rest>
inline void print(const char *format, const First &first, const Rest &...rest) {
    if (*format == '\0') { return; }
    while (*format && !(format[0] == '{' && (format[1] == '}'))) {
        putchar(*format++);
    }
    std::cout << first;
    print(format + 2, rest...);
}

template <typename... Args>
inline void println(const Args &...args) {
    print(args...);
    print('\n');
}

#define println(...)    \
    print(__VA_ARGS__); \
    print('\n');

#include <windows.h>
#include <iostream>

#pragma comment(lib, "user32.lib")

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    println("nCode = {}", nCode);
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT *pMouse = (MSLLHOOKSTRUCT *) lParam;
        println("Mouse Position: ({},{})", pMouse->pt.x, pMouse->pt.y);
    }
    return 0;
}

int main() {
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, 0, 0);

    MSG msg;
    GetMessage(&msg, NULL, NULL, NULL);

    println("finish");
    UnhookWindowsHookEx(hhkLowLevelKybd);
    return 0;
}
