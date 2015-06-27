#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

HWND conWnd = NULL;

char SoftwareVersion[] = "0.1";

// Prototype software for a DigiPet. This is just for the concept, design, and behavior of the code.
// It will be ported later to a small device.

int main(int argc, char *argv[])
{
	conWnd = GetConsoleWindow();
	char consoleTitle[32];
	wsprintf(consoleTitle, "DigiPet version %s", SoftwareVersion);
	SetConsoleTitle(consoleTitle);

	// Set up a back buffer
	HANDLE BackBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	HANDLE ActiveBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(ActiveBuffer);

	//Make curosr invisible
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(BackBuffer, &cursorInfo);
	SetConsoleCursorInfo(ActiveBuffer, &cursorInfo);

	// Set up coordinate stuff and get the back buffer size
	COORD origin = { 0, 0 };
	COORD dims;
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(BackBuffer, &bufferInfo);
	dims = bufferInfo.dwSize;

	int keycode = 0;

	while(true)
	{
		// Handle input
		if (_kbhit() != 0)
		{
			keycode = _getch();
			if (keycode == VK_ESCAPE)
			{
				break;
			}
		}

		// Clear the backguffer
		DWORD count = 0;
		FillConsoleOutputCharacter(BackBuffer, ' ', dims.X * dims.Y, origin, &count);
		SetConsoleCursorPosition(BackBuffer, origin);

		// Render to it
		char message[] = "I'm looping!";
		int len = strlen(message);
		DWORD writeCount = 0;
		WriteConsole(BackBuffer, message, len, &writeCount, NULL);

		// Show back buffer
		HANDLE temp = ActiveBuffer;
		ActiveBuffer = BackBuffer;
		BackBuffer = temp;
		//SetConsoleActiveScreenBuffer(ActiveBuffer);

		Sleep(1);
	}
	
	// Release resources
	CloseHandle(BackBuffer);
	CloseHandle(ActiveBuffer);
	
	return 0;
}