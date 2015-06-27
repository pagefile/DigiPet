#include "Console.h"
#include <conio.h>

HWND conWnd = NULL;

char SoftwareVersion[] = "0.1";

// Prototype software for a DigiPet. This is just for the concept, design, and behavior of the code.
// It will be ported later to a small device.

int main(int argc, char *argv[])
{
    Console con;

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

        char buffer[] = "Hello World!";
        con.Present();

		Sleep(1);
	}
	
	return 0;
}