#include "graphics.h"

void setBackgroundColor(COLORREF color)
{
	CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
	sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

	HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);

	sbInfoEx.dwSize.X = 120; // Set console width to 120 columns
	sbInfoEx.dwSize.Y = 29; 

	COLORREF storedBG = sbInfoEx.ColorTable[0];
	//-- set BG color
	sbInfoEx.ColorTable[0] = color;
	SetConsoleScreenBufferInfoEx(consoleOut, &sbInfoEx);
}

inline void changeTextColor()
{
	std::cout << "\x1b[0m";
}

inline void changeTextColor(RGBCOLOR _fg)
{
	printf("\x1b[38;2;%u;%u;%um", _fg.red, _fg.green, _fg.blue);
}

inline void changeTextColor(RGBCOLOR _fg, RGBCOLOR _bg)
{
	printf("\x1b[38;2;%u;%u;%u;48;2;%u;%u;%um", _fg.red, _fg.green, _fg.blue, _bg.red, _bg.green, _bg.blue);
}

void draw_rectangle(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, RGBCOLOR color)
{
	SetConsoleOutputCP(CP_UTF8);
	changeTextColor(color);
	for (int ix = x_pos + 1; ix < x_pos + width; ++ix) {
		GotoXY(ix, y_pos);
		std::cout << u8"\u2550"; //char(205)
		GotoXY(ix, y_pos + height);
		std::cout << u8"\u2550"; // char(205);
	}
	GotoXY(x_pos, y_pos);
	for (int iy = y_pos + 1; iy < y_pos + height; ++iy) {
		GotoXY(x_pos, iy);
		std::cout << u8"\u2551"; // char(186);
		GotoXY(x_pos + width, iy);
		std::cout << u8"\u2551"; // char(186);
	}
	// draw 4 corners
	GotoXY(x_pos, y_pos);
	std::cout << u8"\u2554"; // char(201);
	GotoXY(x_pos + width, y_pos);
	std::cout << u8"\u2557"; // char(187);
	GotoXY(x_pos, y_pos + height);
	std::cout << u8"\u255A"; // char(200);
	GotoXY(x_pos + width, y_pos + height);
	std::cout << u8"\u255D"; // char(188);
	changeTextColor(color);
}

void draw_rectangle(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, RGBCOLOR color, std::string text, RGBCOLOR txtColor)
{
	SetConsoleOutputCP(CP_UTF8);
	draw_rectangle(x_pos, y_pos, height, width, color);

	changeTextColor(txtColor);
	GotoXY(x_pos + (width - text.size()) / 2, y_pos + height / 2);
	std::cout << text;
	changeTextColor();
}

void filled_rec(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, RGBCOLOR color)
{
	SetConsoleOutputCP(CP_UTF8);
	changeTextColor(color);
	for (int iy = y_pos; iy <= y_pos + height; ++iy) {
		for (int ix = x_pos; ix <= x_pos + width; ++ix) {
			GotoXY(ix, iy);
			std::cout << u8"\u2588"; // char(219);
		}
	}
	changeTextColor();
}

void filled_rec(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, RGBCOLOR color, std::string text, RGBCOLOR txtColor)
{
	filled_rec(x_pos, y_pos, height, width, color);

	changeTextColor(txtColor, color);
	GotoXY(x_pos + (width - text.size()) / 2, y_pos + height / 2);
	std::cout << text;
	GotoXY(x_pos + width + 1, y_pos);
	changeTextColor();
}

void highlightedBox(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, RGBCOLOR color)
{
	SetConsoleOutputCP(CP_UTF8);
	changeTextColor(color);
	for (int ix = x_pos; ix <= x_pos + width; ++ix) {
		GotoXY(ix, y_pos);
		std::cout << u8"\u2588"; // char(219);
		GotoXY(ix, y_pos + height);
		std::cout << u8"\u2588"; // char(219);
	}
	GotoXY(x_pos, y_pos);
	for (int iy = y_pos; iy <= y_pos + height; ++iy) {
		GotoXY(x_pos, iy);
		std::cout << u8"\u2588"; // char(219);
		GotoXY(x_pos + width, iy);
		std::cout << u8"\u2588"; // char(219);
	}
	changeTextColor();
}

void draw_level1() {
	SetConsoleOutputCP(CP_UTF8);
	text_color(colorCode::DARK_YELLOW, colorCode::LIGHT_GRAY);
	GotoXY(92, 9); std::cout << u8"█░░░█▀▀░█░█░█▀▀░█░░░▀█░";
	GotoXY(92, 10); std::cout << u8"█░░░█▀▀░▀▄▀░█▀▀░█░░░░█░";
	GotoXY(92, 11); std::cout << u8"▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀";
}

void draw_level2() {
	SetConsoleOutputCP(CP_UTF8);
	text_color(colorCode::DARK_YELLOW, colorCode::LIGHT_GRAY);
	GotoXY(92, 9); std::cout << u8"█░░░█▀▀░█░█░█▀▀░█░░░▀▀▄";
	GotoXY(92, 10); std::cout << u8"█░░░█▀▀░▀▄▀░█▀▀░█░░░▄▀░";
	GotoXY(92, 11); std::cout << u8"▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀▀";
}

void draw_level3() {
	SetConsoleOutputCP(CP_UTF8);
	text_color(colorCode::DARK_YELLOW, colorCode::LIGHT_GRAY);
	GotoXY(92, 9); std::cout << u8"█░░░█▀▀░█░█░█▀▀░█░░░▀▀█";
	GotoXY(92, 10); std::cout << u8"█░░░█▀▀░▀▄▀░█▀▀░█░░░░▀▄";
	GotoXY(92, 11); std::cout << u8"▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀▀░";
}

void draw_level4() {
	SetConsoleOutputCP(CP_UTF8);
	text_color(colorCode::DARK_YELLOW, colorCode::LIGHT_GRAY);
	GotoXY(92, 9); std::cout << u8"█░░░█▀▀░█░█░█▀▀░█░░░█░█";
	GotoXY(92, 10); std::cout << u8"█░░░█▀▀░▀▄▀░█▀▀░█░░░░▀█";
	GotoXY(92, 11); std::cout << u8"▀▀▀░▀▀▀░░▀░░▀▀▀░▀▀▀░░░▀";
}

void draw_huntingSnake() {
	SetConsoleOutputCP(CP_UTF8);
	text_color(colorCode::BLACK, colorCode::LIGHT_BLUE);
	GotoXY(32, 1); std::cout << u8"░█░█░█░█░█▀█░▀█▀░▀█▀░█▀█░█▀▀░░░█▀▀░█▀█░█▀█░█░█░█▀▀\n";
	GotoXY(32, 2); std::cout << u8"░█▀█░█░█░█░█░░█░░░█░░█░█░█░█░░░▀▀█░█░█░█▀█░█▀▄░█▀▀\n";
	GotoXY(32, 3); std::cout << u8"░▀░▀░▀▀▀░▀░▀░░▀░░▀▀▀░▀░▀░▀▀▀░░░▀▀▀░▀░▀░▀░▀░▀░▀░▀▀▀\n";
	//SetConsoleOutputCP(GetACP());
}

void draw_ButtonW() {
	//draw_rectangle(94, 10, 1, 3, colorCode::DARK_BLUE, colorCode::DARK_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 20, 1, 3, { 63, 199, 212 });
	GotoXY(95, 21);
	changeTextColor({ 0, 0, 0 }, { 63, 199, 212 });
	cout << "W" << u8"\u2191";

	//draw_rectangle(88, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(88, 23, 1, 3, { 208, 75, 81 });
	GotoXY(89, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "A" << u8"\u2190";

	//draw_rectangle(94, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 23, 1, 3, { 208, 75, 81 });
	GotoXY(95, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "S" << u8"\u2193";

	//draw_rectangle(100, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(100, 23, 1, 3, { 208, 75, 81 });
	GotoXY(101, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "D" << u8"\u2192";
}

void draw_ButtonA() {
	//draw_rectangle(94, 10, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 20, 1, 3, { 208, 75, 81 });
	GotoXY(95, 21);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "W" << u8"\u2191";

	//draw_rectangle(88, 13, 1, 3, colorCode::DARK_BLUE, colorCode::DARK_BLUE, "", -1, colorCode::BLACK);
	filled_rec(88, 23, 1, 3, { 63, 199, 212 });
	GotoXY(89, 24);
	changeTextColor({ 0, 0, 0 }, { 63, 199, 212 });
	cout << "A" << u8"\u2190";

	//draw_rectangle(94, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 23, 1, 3, { 208, 75, 81 });
	GotoXY(95, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "S" << u8"\u2193";

	//draw_rectangle(100, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(100, 23, 1, 3, { 208, 75, 81 });
	GotoXY(101, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "D" << u8"\u2192";
}

void draw_ButtonS() {
	//draw_rectangle(94, 10, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 20, 1, 3, { 208, 75, 81 });
	GotoXY(95, 21);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "W" << u8"\u2191";

	//draw_rectangle(88, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(88, 23, 1, 3, { 208, 75, 81 });
	GotoXY(89, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "A" << u8"\u2190";

	//draw_rectangle(94, 13, 1, 3, colorCode::DARK_BLUE, colorCode::DARK_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 23, 1, 3, { 63, 199, 212 });
	GotoXY(95, 24);
	changeTextColor({ 0, 0, 0 }, { 63, 199, 212 });
	cout << "S" << u8"\u2193";

	//draw_rectangle(100, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(100, 23, 1, 3, { 208, 75, 81 });
	GotoXY(101, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "D" << u8"\u2192";
}

void draw_ButtonD() {
	//draw_rectangle(94, 10, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 20, 1, 3, { 208, 75, 81 });
	GotoXY(95, 21);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "W" << u8"\u2191";

	//draw_rectangle(88, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(88, 23, 1, 3, { 208, 75, 81 });
	GotoXY(89, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "A" << u8"\u2190";

	//draw_rectangle(94, 13, 1, 3, colorCode::LIGHT_BLUE, colorCode::LIGHT_BLUE, "", -1, colorCode::BLACK);
	filled_rec(94, 23, 1, 3, { 208, 75, 81 });
	GotoXY(95, 24);
	changeTextColor({ 0, 0, 0 }, { 208, 75, 81 });
	cout << "S" << u8"\u2193";

	//draw_rectangle(100, 13, 1, 3, colorCode::DARK_BLUE, colorCode::DARK_BLUE, "", -1, colorCode::BLACK);
	filled_rec(100, 23, 1, 3, { 63, 199, 212 });
	GotoXY(101, 24);
	changeTextColor({ 0, 0, 0 }, { 63, 199, 212 });
	cout << "D" << u8"\u2192";
}

void pause_game() {
	//system("cls");
	//draw_matchBoard(10, 20, 10, 20, scor, le, 2, 0, "", 1);
}
