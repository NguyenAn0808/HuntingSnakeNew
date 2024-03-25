#include "arts.h"
#include "ConsoleWindow.h"
#include <iostream>
#include "graphics.h"

void drawMenuSnake(int pos_x, int pos_y, std::string pic)
{
    GotoXY(pos_x, pos_y);
    for (auto i : pic) {
        switch (i)
        {
        case '1': case '2':
            changeTextColor({ 0, 208, 0 });
            break;
        case '3': case '4': case '6': case '7': case '5':
            changeTextColor({ 224, 188, 118 });
            break;
        default:
            changeTextColor({ 225, 225, 225 });
            break;
        }
        if (i > 32) cout << (char)219;
        else cout << i;
    }
    changeTextColor();
}

void drawMAP1(int pos_x, int pos_y, std::string pic)
{
    SetConsoleOutputCP(CP_UTF8);
    GotoXY(pos_x, pos_y);
    for (auto i : pic) {
        switch (i)
        {
        case '.':
            changeTextColor({ 254, 195, 255 });
            break;
        case '+':
            changeTextColor({ 60, 91, 113 });
            break;
        case '-':
            changeTextColor({ 213, 174, 152 });
            break;
        case '*':
            changeTextColor({ 147, 92 ,61 });
            break;
        case '#':
            changeTextColor({ 39, 60, 74 });
            break;
        case 'o':
            changeTextColor({ 98, 141, 172 });
            break;
        case 'L':
            changeTextColor({ 62, 37, 15 });
            break;
        case '0':
            changeTextColor({ 124, 160, 186 });
            break;
        case 'T':
            changeTextColor({ 87, 133, 85 });
            break;
        case 'B':
            changeTextColor({ 0, 0, 0 });
            break;
        default:
            text_color(BG_COLOR, colorCode::WHITE);
            //changeTextColor({ 95, 83, 84 });
            break;
        }
        if (i > 32) cout << u8"\u2588";
        else cout << i;
    }
}

void drawMAP2(int pos_x, int pos_y, std::string pic)
{
    SetConsoleOutputCP(CP_UTF8);
    GotoXY(pos_x, pos_y);
    for (auto i : pic) {
        switch (i)
        {
        case '2':
            changeTextColor({ 38, 61, 96 });
            break;
        case '1':
            changeTextColor({ 95, 83, 84 });
            break;
        case 'X':
            changeTextColor({ 48, 73, 47 });
            break;
        case 'B':
            changeTextColor({ 0, 0, 0 });
            break;
        default:
            text_color(BG_COLOR, colorCode::WHITE);
            //changeTextColor({ 95, 83, 84 });
            break;
        }
        if (i > 32) cout << u8"\u2588";
        else cout << i;
    }

}

void drawMAP3(int pos_x, int pos_y, std::string pic)
{
    SetConsoleOutputCP(CP_UTF8);
    GotoXY(pos_x, pos_y);
    for (auto i : pic) {
        switch (i)
        {
        case '.': 
            changeTextColor({ 192, 225, 246 });
            break;
        case '+':
            changeTextColor({ 89, 54, 21 });
            break;
        case '-':
            changeTextColor({ 128, 210, 79 });
            break;
        case '*':
            changeTextColor({ 205, 123, 49 });
            break;
        case '#':
            changeTextColor({ 142, 85, 34 });
            break;
        case 'T':
            changeTextColor({ 173, 104, 41 });
            break;
        case 'L':
            changeTextColor({ 62, 37, 15 });
            break;
        case '1':
            changeTextColor({ 39, 74, 19 });
            break;
        case '2':
            changeTextColor({ 73, 137, 35 });
            break;
        case 'M':
            changeTextColor({ 170, 214, 243 });
            break;
        case 'I':
            changeTextColor({ 245, 245, 245 });
            break;
        case 'B':
            changeTextColor({ 0, 0, 0 });
            break;
        default:
            text_color(BG_COLOR, colorCode::WHITE);
            //changeTextColor({ 95, 83, 84 });
            break;
        }
        if (i > 32) cout << u8"\u2588";
        else cout << i;
    }
}

void drawMAP4(int pos_x, int pos_y, std::string pic)
{
    SetConsoleOutputCP(CP_UTF8);
    GotoXY(pos_x, pos_y);
    for (auto i : pic) {
        switch (i)
        {
        case '+':
            changeTextColor({ 176, 110, 84 });
            break;
        case '-':
            changeTextColor({ 211, 140, 116 });
            break;
        case '*':
            changeTextColor({ 123, 69, 58 });
            break;
        case '.':
            changeTextColor({ 251, 213, 179 });
            break;
        case 'o':
            changeTextColor({ 123, 69, 58 });
            break;
        case 'W':
            changeTextColor({ 245, 245, 245 });
            break;
        case 'P':
            changeTextColor({ 210, 179, 158 });
            break;
        case 'T':
            changeTextColor({ 196, 117, 78 });
            break;
        case 'B':
            changeTextColor({ 0, 0, 0 });
            break;
        default:
            text_color(BG_COLOR, colorCode::WHITE);
            //changeTextColor({ 95, 83, 84 });
            break;
        }
        if (i > 32) cout << u8"\u2588";
        else cout << i;
    }

    //draw_huntingSnake();
}

void draw_INFOR(int pos_x, int pos_y, std::string pic)
{
    SetConsoleOutputCP(CP_UTF8);
    GotoXY(pos_x, pos_y);
    int k = 1;
    for (auto i : pic) {
        switch (i)
        {
        case '-':
            changeTextColor({ 95, 83, 84 });
            break;
        case '*':
            changeTextColor({ 37, 67, 110 });
            break;
        case 'B':
            changeTextColor({ 97, 61, 27 });
            break;
        case 'W':
            changeTextColor({ 22, 40, 66 });
            break;
        case 'R':
            changeTextColor({ 97, 19, 19 });
            break;
        case 'P':
            changeTextColor({ 219, 74, 74 });
            break;
        case 'G':
            changeTextColor({ 38, 135, 91 });
            break;
        case 'D':
            changeTextColor({ 19, 68, 46 });
            break;
        case 'O':
            changeTextColor({ 140, 19, 30 });
            break;
        case 'T':
            changeTextColor({ 162, 91, 98 });
            break;
        case 'E':
            changeTextColor({ 0, 0, 0 });
            break;
        case 'I':
            changeTextColor({ 29, 31, 38 });
            break;
        case 'X':
            changeTextColor({ 2, 122, 18 });
            break;
        default:
            text_color(BG_COLOR, colorCode::BLACK);
            break;
        }
        if (i == '\n') {
            GotoXY(pos_x, pos_y + k);
            k++;
        }
        cout << u8"\u2588";
    }
}

void draw_snakeWIN(int pos_x, int pos_y, std::string pic)
{
    SetConsoleOutputCP(CP_UTF8);
    GotoXY(pos_x, pos_y);
    int k = 1;
    for (auto i : pic) {
        switch (i)
        {
        case '.':
            changeTextColor({ 32, 49, 32 });
            break;
        case '-':
            changeTextColor({ 98, 205, 98 });
            break;
        case '*':
            changeTextColor({ 208, 147, 67 });
            break;
        case '#':
            changeTextColor({ 245, 245, 245 });
            break;
        case '+':
            changeTextColor({ 32, 49, 32 });
            break;
        case '0':
            changeTextColor({ 162, 91, 98 });
            break;
        case 'W':
            changeTextColor({ 245, 245, 245 });
            break;
        case 'T':
            changeTextColor({ 90, 168, 170 });
            break;
        case 'L':
            changeTextColor({ 116, 182, 183 });
            break;
        default:
            changeTextColor({ 162, 91, 98 });
            break;
        }
        if (i == '\n') {
            GotoXY(pos_x, pos_y + k);
            k++;
        }
        cout << u8"\u2588";
    }
    text_color(colorCode::DARK_YELLOW, colorCode::LIGHT_GRAY);

    GotoXY(2, 8); std::cout << u8"██╗   ██╗  ██████╗  ██╗   ██╗\n";
    GotoXY(2, 9); std::cout << u8"╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║\n";
    GotoXY(2, 10); std::cout << u8" ╚████╔╝  ██║   ██║ ██║   ██║\n";
    GotoXY(2, 11); std::cout << u8"  ╚██╔╝   ██║   ██║ ██║   ██║\n";
    GotoXY(2, 12); std::cout << u8"   ██║    ╚██████╔╝ ╚██████╔╝\n";
    GotoXY(2, 13); std::cout << u8"   ╚═╝     ╚═════╝   ╚═════╝\n";

    GotoXY(4, 14); std::cout << u8"██╗    ██╗██╗███╗   ██╗\n";
    GotoXY(4, 15); std::cout << u8"██║    ██║██║████╗  ██║\n";
    GotoXY(4, 16); std::cout << u8"██║ █╗ ██║██║██╔██╗ ██║\n";
    GotoXY(4, 17); std::cout << u8"██║███╗██║██║██║╚██╗██║\n";
    GotoXY(4, 18); std::cout << u8"╚███╔███╔╝██║██║ ╚████║\n";
    GotoXY(4, 19); std::cout << u8" ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝\n";

}

void draw_snakeDEAD(int pos_x, int pos_y, std::string pic)
{
    SetConsoleOutputCP(CP_UTF8);
    GotoXY(pos_x, pos_y);
    int k = 1;
    for (auto i : pic) {
        switch (i)
        {
        case '.':
            changeTextColor({ 32, 49, 32 });
            break;
        case '-':
            changeTextColor({ 98, 205, 98 });
            break;
        case '*':
            changeTextColor({ 162, 91, 98 });
            break;
        case '#':
            changeTextColor({ 245, 245, 245 });
            break;
        case '+':
            changeTextColor({ 32, 49, 32 });
            break;
        case '0':
            changeTextColor({ 162, 91, 98 });
            break;
        case '5':
            changeTextColor({ 215, 84, 90 });
            break;
        case 'o':
            changeTextColor({ 162, 91, 98 });
            break;
        case 'c':
            changeTextColor({ 96, 122, 194 });
            break;
        default:
            changeTextColor({ 162, 91, 98 });
            break;
        }
        if (i == '\n') {
            GotoXY(pos_x, pos_y + k);
            k++;
        }
        cout << u8"\u2588";
    }
    text_color(colorCode::DARK_YELLOW, colorCode::LIGHT_GRAY);

    GotoXY(2, 8); std::cout << u8"██╗   ██╗  ██████╗  ██╗   ██╗\n";
    GotoXY(2, 9); std::cout << u8"╚██╗ ██╔╝ ██╔═══██╗ ██║   ██║\n";
    GotoXY(2, 10); std::cout << u8" ╚████╔╝  ██║   ██║ ██║   ██║\n";
    GotoXY(2, 11); std::cout << u8"  ╚██╔╝   ██║   ██║ ██║   ██║\n";
    GotoXY(2, 12); std::cout << u8"   ██║    ╚██████╔╝ ╚██████╔╝\n";
    GotoXY(2, 13); std::cout << u8"   ╚═╝     ╚═════╝   ╚═════╝\n";

    GotoXY(2, 14); std::cout << u8"██████╗ ███████╗ █████╗ ██████╗\n";
    GotoXY(2, 15); std::cout << u8"██╔══██╗██╔════╝██╔══██╗██╔══██╗\n";
    GotoXY(2, 16); std::cout << u8"██║  ██║█████╗  ███████║██║  ██║\n";
    GotoXY(2, 17); std::cout << u8"██║  ██║██╔══╝  ██╔══██║██║  ██║\n";
    GotoXY(2, 18); std::cout << u8"██████╔╝███████╗██║  ██║██████╔╝\n";
    GotoXY(2, 19); std::cout << u8" ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═════╝\n";
}

void deleteArt(int pos_x, int pos_y, std::string pic) {
    GotoXY(pos_x, pos_y);
    for (const char i : pic) {
        if (i > 32) cout << " ";
        else {
            cout << i;
        }
    }
}
