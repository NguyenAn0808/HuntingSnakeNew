#include "GameMatch.h"
#include "snake.h"
#include "graphics.h"
#include "arts.h"

// change text inside color
void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


//	draw_matchBoard
void draw_matchBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int& SCORE, int& LEVEL, int line_color, int bg_color, std::string text, int txtColor) {

	draw_huntingSnake();

	drawMAP1(x_pos, y_pos, MAP1);

	//drawInfor(width + 5, y_pos, inforBoard);
	draw_INFOR(width + 5, y_pos, infor_Board);


	switch (LEVEL)
	{
		case 1:
			draw_level1();
			break;
		case 2:
			draw_level2();
			break;
		case 3:
			draw_level3();
			break;
		case 4:
			draw_level4();
			break;
	}
	

}

// draw infor board
void draw_infoBoard(unsigned int x_pos, unsigned int y_pos, unsigned int height, unsigned int width, int txtColor, int bg_color, int line_color, std::string text) {
 	SetConsoleOutputCP(CP_UTF8);

	changeTextColor({ 255, 0, 0 }, {255, 255, 0});
	GotoXY(x_pos + 6, y_pos + 3); cout << "TUTORIAL";
	changeTextColor();

	/*
	filled_rec(x_pos + 8, y_pos + 5, 1, 3, { 0, 255, 0 });
	GotoXY(x_pos + 9, y_pos + 6);
	changeTextColor({ 0, 0, 0 }, { 0, 255, 0 });
	cout << "W" << u8"\u2191";
	//GotoXY(x_pos + 8 + 3, y_pos + 5);
	changeTextColor();

	filled_rec(x_pos + 2, y_pos + 8, 1, 3, { 0, 255, 0 });
	//text_color(colorCode::LIGHT_BLUE, colorCode::BLACK);
	GotoXY(x_pos + 3, y_pos + 9);
	changeTextColor({ 0, 0, 0 }, { 0, 255, 0 });
	cout << "A" << u8"\u2190";
	changeTextColor();

	filled_rec(x_pos + 8, y_pos + 8, 1, 3, { 0, 255, 0 });
	//text_color(colorCode::LIGHT_BLUE, colorCode::BLACK);
	GotoXY(x_pos + 9, y_pos + 9);
	changeTextColor({ 0, 0, 0 }, { 0, 255, 0 });
	cout << "S" << u8"\u2193";
	changeTextColor();

	filled_rec(x_pos + 14, y_pos + 8, 1, 3, { 0, 255, 0 });
	//text_color(colorCode::LIGHT_BLUE, colorCode::BLACK);
	GotoXY(x_pos + 15, y_pos + 9);
	changeTextColor({ 0, 0, 0 }, { 0, 255, 0 });
	cout << "D" << u8"\u2192";
	changeTextColor();
	*/
	
	//text_color(colorCode::DARK_YELLOW, colorCode::BLACK);
	GotoXY(x_pos + 3, y_pos + 11); cout << "PAUSE:  PRESS U";
	GotoXY(x_pos + 3, y_pos + 12); cout << "EXIT:   PRESS ESC";

	GotoXY(x_pos+1, y_pos + 14);
	for (int i = 1; i <= width-1; i++) {
		cout << u8"\u2550";
	}
	text_color(colorCode::DARK_YELLOW, colorCode::BLACK);
	GotoXY(x_pos + 12, y_pos + 15); cout << "SCORE";
}

// draw obstacle from create_obs
void draw_obstacle(Point obs[], int obs_nums) {
	for (int i = 0; i < obs_nums; i++) {
		GotoXY(obs[i].x, obs[i].y);
		cout << u8"\u2588";
	}
}


