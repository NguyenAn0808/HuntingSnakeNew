#pragma once
#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Snake.h"
#include "graphics.h"
// macro for console background color & text color
#define BG_COLOR 1
#define TXT_COLOR 7


#define BG_COLOR colorCode::LIGHT_CYAN
#define TXT_COLOR colorCode::LIGHT_YELLOW
#define BG_RGB rgb(163, 244, 255)
#define TXT_RGB {12, 45, 87}
const long nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
const long nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);


struct axis //store terminal's axis
{
	int x;
	int y;
};

axis getTermSize(); // get terminal size

void text_color(int background_color, int text_color);

void GotoXY(int x, int y);

void LoadConsole();
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void ShowScrollbar(BOOL Show);
void SetConsolePosition(int x, int y);
void LockConsolePosition();
void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void MaximizeConsoleWindow();
void ShowConsoleCursor(bool show); // show/unshow the cursor of the terminal

void mainMenu(); // main menu of the program
