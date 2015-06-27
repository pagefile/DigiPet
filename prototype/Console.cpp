#include "Console.h"

Console::Console() : charBuffer(NULL), outputHandle(NULL)
{
    // Get console info
    outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    memset(&info, 0, sizeof(info));
    GetConsoleScreenBufferInfo(outputHandle, &info);

    // Set data
    bufferDims = info.dwSize;
    charBuffer = new CHAR_INFO[info.dwSize.X * info.dwSize.Y];
    memset(charBuffer, 0, info.dwSize.X * info.dwSize.Y);

    for(int i = 0; i < info.dwSize.X * info.dwSize.Y; i++)
    {
        charBuffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }

    // Make curosr invisible
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 0;
    SetConsoleCursorInfo(outputHandle, &cursorInfo);
}

Console::~Console()
{
    CloseHandle(outputHandle);
    if(charBuffer != NULL)
    {
        delete charBuffer;
    }
}


void Console::SetChar(char c, int x, int y)
{
    charBuffer[DimToIndex(x, y)].Char.AsciiChar = c;
}


int Console::DimToIndex(int x, int y)
{
    return y * bufferDims.X + x;
}


void Console::Present()
{
    SMALL_RECT rect;
    COORD origin;
    origin.X = 0;
    origin.Y = 0;
    rect.Top = 0;
    rect.Left = 0;
    rect.Right = bufferDims.X;
    rect.Bottom = bufferDims.Y;
    WriteConsoleOutput(outputHandle, charBuffer, bufferDims, origin, &rect);
}