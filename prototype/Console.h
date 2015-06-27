#pragma once

#include <Windows.h>
#include <string>

using namespace std;

// Class to make console functionality easier to use.
class Console
{

    // TODO: Write overloads for functions that take coordinates

public:
    Console();
    ~Console();


    void SetChar(char c, int x, int y);

    void Present();

private:
    HANDLE outputHandle;
    CHAR_INFO *charBuffer;
    COORD bufferDims;

    int DimToIndex(int x, int y);
};