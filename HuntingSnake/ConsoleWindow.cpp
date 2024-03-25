#include "ConsoleWindow.h"
#include "GenerateMap.h"
#include "snake.h"
#include "arts.h"


int man = 1;

axis getTermSize()
{
    axis res;

    // get terminal's size
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // calculate the size of terminal
    res.x = info.srWindow.Right - info.srWindow.Left + 1;
    res.y = info.srWindow.Bottom - info.srWindow.Top + 1;

    return res;
}

void text_color(int background_color, int text_color)
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = background_color * 16 + text_color;
    SetConsoleTextAttribute(color, color_code);
}

void GotoXY(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void LoadConsole()
{
    SetWindowSize(120, 30);
    SetScreenBufferSize(120, 30);

    DisableResizeWindow();
    DisableCtrButton(0, 0, 0);
    ShowScrollbar(0);
    SetConsolePosition(250, 250);
    LockConsolePosition();
}

void DisableResizeWindow()
{
    //get handle window console
    HWND hWnd = GetConsoleWindow();
    // don't allow to change size console through drag the edges or corners
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableCtrButton(bool Close, bool Min, bool Max)
{
    //get handle window console
    HWND hWnd = GetConsoleWindow();
    //get menu of console
    HMENU hMenu = GetSystemMenu(hWnd, false);

    //1 - off, 0 - on
    if (Close == 1)
    {
        //delete close button
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        //delete min button
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        //delete max button
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    //SB_BOTH to hide both horizontal & vertical scrollbars
    //0 - off, 1 - on
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void SetConsolePosition(int x, int y)
{
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void LockConsolePosition() {
    HWND consoleWindow = GetConsoleWindow();
    //get style window console
    LONG_PTR windowStyle = GetWindowLongPtr(consoleWindow, GWL_STYLE);

    // delete flag WS_CAPTION out of the window
    windowStyle &= ~WS_CAPTION;

    SetWindowLongPtr(consoleWindow, GWL_STYLE, windowStyle);

    // set size window
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);
}

void MaximizeConsoleWindow()
{
    HWND consoleWindow = GetConsoleWindow();
    //set console at maximize size
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetScreenBufferSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}

void ShowConsoleCursor(bool show)
{
    // using Win32 API to make the cursor disappear
    // Reference: https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = show; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void mainMenu() {
    // Fix console
    LoadConsole();
    // turn off cursor blinking
    ShowConsoleCursor(false);
    // define position of the menu and size of each button
    unsigned int x_menu = (getTermSize().x - 20) / 2 + 40,
        y_menu = (getTermSize().y - 20) / 2,
        rec_width = 20,
        rec_height = 4;

    /*DO NOT TOUCH*/
    // set color for the background, color could be change in the macro in ConsoleWindow.h
    COLORREF bgCol = rgb(255, 176, 176);
    setBackgroundColor(BG_RGB);
    changeTextColor(TXT_RGB);
    drawMenuSnake(0, 0, decorSnake);
    //drawHSnake(x_menu - (42 / 2), y_menu);

    // draw menu
    draw_rectangle(x_menu, y_menu, rec_height, rec_width, TXT_RGB, "New Game", TXT_RGB);
    draw_rectangle(x_menu, y_menu + 5, rec_height, rec_width, TXT_RGB, "Load Game", TXT_RGB);
    draw_rectangle(x_menu, y_menu + 10, rec_height, rec_width, TXT_RGB, "Achievements", TXT_RGB);
    draw_rectangle(x_menu, y_menu + 15, rec_height, rec_width, TXT_RGB, "Settings", TXT_RGB);


    // define variables use for navigate through the menu
    unsigned int x_pointer = x_menu, y_pointer = y_menu;
    unsigned int x_prev = x_menu, y_prev = y_menu;
    bool check = true, isEnter = false;
    int selection;

    while (isEnter == false) {
        GotoXY(x_pointer, y_pointer);

        // highlitght the current option that the user choose, only if any key is pressed
        if (check) {
            //if the user navigate to the next button, the x_prev and y_prev variables will store the previous axis
            // then turn off the hightlight of the box by set the first paraameter of highlightedBox() to false
            GotoXY(x_prev, y_prev);
            draw_rectangle(x_prev, y_prev, rec_height, rec_width, TXT_RGB);

            // change the x_prev & y_prev to the current position
            x_prev = x_pointer;
            y_prev = y_pointer;

            // hightlight the current button
            highlightedBox(x_pointer, y_pointer, rec_height, rec_width, { 225, 0, 0 });

            // set to false to mark that now there's no button pressed
            check = false;
        }

        // navigate through the menu
        if (_kbhit()) { // if any key is pressed
            check = true;

            // variable to receive user input
            char handle;
            handle = toupper(_getch());
            Sleep(50);

            switch (handle)
            {
            case 'S': case 'P': // if user pressed S or 'Arrow Down'
                // move pointer down to the next button
                y_pointer += 5;
                // if pointer is out of range => set the pointer to the first position
                if (y_pointer > y_menu + 15) y_pointer = y_menu;
                GotoXY(x_pointer, y_pointer);
                break;
            case 'W': case 'H': // if user pressed W or 'Arrow Up'
                // move pointer up to the next button
                y_pointer -= 5;
                // if pointer is out of range => set the pointer to the last button
                if (y_pointer < y_menu) y_pointer = y_menu + 15;
                GotoXY(x_pointer, y_pointer);

                break;
            case 13: // if user pressed 'Enter'
                selection = (y_pointer / y_menu);
                isEnter  = true;
                break;
            }
        }
    }
    switch (selection)
    {
    case 1:
        StartGame();
        LoadGame(man);
        break;
    default:
        filled_rec(6, 6, 5, 5, { 0, 255, 255 }, "test", { 255, 0, 0 });
        break;
    }
}
