#include "GameMatch.h"
#include "snake.h"

// change text inside color
void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


/*
	void draw_matchBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int &SCORE, int &LEVEL) {
	GotoXY(x_pos + 20, y_pos - 2);
	draw_rec(x_pos, y_pos, height, width);
	draw_infoBoard(width + 5, y_pos, height - 4, width - 48, 2, 0, 5);
	draw_underline(x_pos, height + 4, 2, width - 50, "MAP: ", 1, 2, 0, 5);
	draw_underline(width - 50 + 2, height + 4, 2, width - (width - 50) - 1, "PLAYER: ", 1, 2, 0, 5);
	draw_underline(width + 5, height, 3, width - 50 + 2, "SCORE: ", SCORE, 2, 0, 5);
	draw_underline(width + 5, height + 4, 2, width - 50 + 2, "LEVEL: ", LEVEL, 2, 0, 5);
}
*/


//	draw_matchBoard
void draw_matchBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int& SCORE, int& LEVEL, int line_color, int bg_color, std::string text, int txtColor) {

	draw_rectangle(x_pos, y_pos, height, width, line_color, bg_color, text, txtColor);

	draw_infoBoard(width + 5, y_pos, height - 4, width - 48, 2, 0, 5, "");

	draw_rectangle(x_pos, height + 4, 2, width - 50, line_color, bg_color, "MAP", txtColor);
	draw_rectangle(width - 50 + 2, height + 4, 2, width - (width - 50) - 2, line_color, bg_color, "PLAYER", txtColor);
	draw_rectangle(width + 5, height, 3, width - 50 + 2, line_color, bg_color, "SCORE", txtColor);
	draw_rectangle(width + 5, height + 4, 2, width - 50 + 2, line_color, bg_color, "LEVEL", txtColor);
}

// draw infor board
void draw_infoBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int txtColor, int bg_color, int line_color, std::string text) {


	draw_rectangle(x_pos, y_pos, height, width, line_color, bg_color, text, txtColor);
	setTextColor(2);
	GotoXY(x_pos + 6, y_pos + 3); cout << "TUTORIAL";

	draw_rectangle(x_pos + 8, y_pos + 5, 2, 4, line_color, bg_color, "W", txtColor);
	draw_rectangle(x_pos + 2, y_pos + 8, 2, 4, line_color, bg_color, "A", txtColor);
	draw_rectangle(x_pos + 8, y_pos + 8, 2, 4, line_color, bg_color, "S", txtColor);
	draw_rectangle(x_pos + 14, y_pos + 8, 2, 4, line_color, bg_color, "D", txtColor);

	GotoXY(x_pos + 3, y_pos + 13); cout << "PAUSE:         PRESS U";
	GotoXY(x_pos + 3, y_pos + 15); cout << "EXIT:          PRESS ESC";
}

// draw obstacle from create_obs
void draw_obstacle(Point obs[], int obs_nums) {
	for (int i = 0; i < obs_nums; i++) {
		GotoXY(obs[i].x, obs[i].y);
		cout << char(219);
	}
}


