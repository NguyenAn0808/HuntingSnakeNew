#include "Snake.h"
#include "ConsoleWindow.h"
#include "GameMatch.h"
#include "GenerateMap.h"

// Random number generator (rng) generates seed to random number [0, 2^64 - 1]
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Declare Global Variables, Structs
Point Snake[MAX_SIZE_SNAKE]; // Snake
Point Food[MAX_SIZE_FOOD]; // Food
Point Center; // Center coordinates of Gate
Point Gate[5]; // Coordinates of Gate
Point* obs = new Point[1000];
Point const_obs[1000];

string str[MAX_SIZE_SNAKE];

int STATE; // DEAD or ALIVE
int SPEED; // Current speed (Speed increase with each level)
int ID_Food; // Current index of food 
int LEVEL = 1; // Current level (Maximum is 5 levels)
int SCORE; // Current score
int TYPE; // Type of Gate (4 types directions = 4 types gates)
int cntGate; // index of coordinates of Gate
int Snake_Size; // Size of snake, initially 6 units and maximum is 22 units
int obs_nums; // Size of obstacles
int const_obs_nums;

char CHAR_LOCK; // At a moment, there is one direction that snake cannot move to
char MOVING; // At a moment, there are three directions that snake can move

bool GateDraw; // Gate exist or not
bool up = false;
bool WIN = false;

float addTime; // Control the speed between rows and columns 
// Speed through rows < speed through columns (number of columns > number of rows)

float DeltaSpeed = 0; // Control the speed when move to next level


int lev = 1; // Current level (Maximum is 5 levels)

int getValue(int lev) {
	return lev;
}

void StartGame()
{
	system("cls"); // Clear screen
	ResetData(); // Intialize original data
	STATE = 1; // ALIVE (Running thread)
	DrawSnake(MSSV); // Draw snake with MSSV of four members in group
}
void LoadGame(int &lev)
{
	
	switch (lev)
	{
	case 1:
		draw_matchBoard(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, SCORE, LEVEL, 2, 0, "", 1);
		break;
	case 2:
		play_match2(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, obs, obs_nums, SCORE, LEVEL);
		break;
	case 3:
		play_match3(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, obs, obs_nums, SCORE, LEVEL);
		break;
	case 4:
		create_obstacle_4(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, obs, obs_nums, const_obs, const_obs_nums);
		// draw match board
		draw_matchBoard(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, SCORE, LEVEL, 2, 0, "", 1);
		break;
	}
	

	thread thread_obj(ThreadFunction); // Create thread for snake
	HANDLE handle_thread_obj = thread_obj.native_handle(); // Take handle of thread

	while (true)
	{
		char temp = toupper(_getch()); // Get character from the keyboard (including 4 arrows, WASD, ...)
		if (STATE == 1)
		{
			ResumeThread(handle_thread_obj);

			if (temp == 'U') // 'P' Key to Pause Game
				PauseGame(handle_thread_obj);
			else if (temp == 27) // 'ESC' Key to Exit Game
			{
				ExitGame(handle_thread_obj);
				return;
			}

			// H, P, M, K -> 4 arrows when transform into characters

			if ((temp == 'W' || temp == 'S' || temp == 'A' || temp == 'D' ||
				temp == 'H' || temp == 'P' || temp == 'M' || temp == 'K') && temp != CHAR_LOCK)
			{
				MOVING = temp; // Next movement of snake
			}
		}

	}
}
void PauseGame(HANDLE t)
{
	SuspendThread(t);
}
void ExitGame(HANDLE t)
{
	system("cls");
	TerminateThread(t, 0);
}

/*
void LoadMap()
{

	// PLAY TEST
	//play_match2(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, obs, obs_nums, SCORE, LEVEL);
	//play_match3(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, obs, obs_nums, SCORE, LEVEL);
	//play_match4(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, obs, obs_nums, up, const_obs, const_obs_nums, SCORE, LEVEL);


	create_obstacle_4(x_pos, y_pos, WIDTH_BOARD, HEIGHT_BOARD, obs, obs_nums, const_obs, const_obs_nums);
	// draw match board
	draw_matchBoard(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, SCORE, LEVEL, 2, 0, "", 1);
	// Move obstacle
	while (true) {
		move_obs(x_pos, y_pos, WIDTH_BOARD, HEIGHT_BOARD, obs, obs_nums, up, const_obs, const_obs_nums);
		// Set movable obstacle speed
		Sleep(65);
	}

}
*/

void ProcessDead()
{
	STATE = 0; // DEAD
	GotoXY(35, 1);
	cout << "GAME OVER\n";
	GotoXY(35, 2);
	system("pause");
}

void ProcessWin()
{
	GotoXY(35, 1);
	cout << "YOU WIN\n";
	GotoXY(35, 2);
	system("pause");
}

void ResetData()
{
	//Initialize the global variables, structs
	for (int i = 0; i < cntGate; i++)
		Gate[i] = { 0, 0 };

	cntGate = 0;

	SPEED = 1;
	addTime = 0;
	Snake_Size = 6 + MAX_SIZE_FOOD * (LEVEL - 1);

	CHAR_LOCK = 'A';
	MOVING = 'D';
		
	ID_Food = 0;

	int Init = 10 / 2 + 5;

	//Initialize the coordinates of snake

	Snake[0] = { Init, Init };
	Snake[1] = { Init - 1, Init };
	Snake[2] = { Init - 2, Init };
	Snake[3] = { Init - 3, Init };
	Snake[4] = { Init - 4, Init };
	Snake[5] = { Init - 5, Init };

	GenerateFood(); // Create food array
	system("cls");
	obs_nums = 0;
	obs = (Point*)calloc(1000, sizeof(Point));
}

void ThreadFunction()
{

	int leve = getValue(lev);
	while (true)
	{
		switch (leve)
		{
		case 4:
			move_obs(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, obs, obs_nums, up, const_obs, const_obs_nums);
		}

		if (STATE == 1) // If snake ALIVE -> continue
		{
			EraseOldSnake(); // Erase old snake and draw new snake
			switch (MOVING)
			{
				// WASD Key   W: Up, S: Down, A: Left, D: Right
				// Arrow Keys H: Up, P: Down, K: Left, M: Right
				// Addtime set speed different between columns and rows
			case 'W': case 'H':
			{
				MoveUp();
				CHAR_LOCK = (MOVING == 'W' ? 'S' : 'P');
				addTime = 0.35F;
				break;
			}

			case 'S': case 'P':
			{
				MoveDown();
				CHAR_LOCK = (MOVING == 'S' ? 'W' : 'H');
				addTime = 0.35F;
				break;
			}

			case 'A': case 'K':
			{
				MoveLeft();
				CHAR_LOCK = (MOVING == 'A' ? 'D' : 'M');
				addTime = 0;
				break;
			}

			case 'D': case 'M':
			{
				MoveRight();
				CHAR_LOCK = (MOVING == 'D' ? 'A' : 'K');
				addTime = 0;
				break;
			}

			default:
				break;
			}
		}

		DrawSnake(MSSV); // After one move, draw new snake because of the change of coordinates
		ProcessGate(lev); // Process if meet the conditions to create the gate
		Sleep(100 / (SPEED + DeltaSpeed - addTime)); // Sleep function will set the speed of snake
	}
}

void DrawSnake(const string& str) // With str is MSSV
{
	// Draw head of snake
	GotoXY(Snake[0].x, Snake[0].y);
	text_color(0, 4); // Color of head will be different from body
	cout << str[0];

	for (int i = 1; i < Snake_Size; i++)
	{
		GotoXY(Snake[i].x, Snake[i].y);
		text_color(0, 10);
		cout << str[i]; // Draw body of snake
	}
}
void DrawFood()
{
	GotoXY(Food[ID_Food].x, Food[ID_Food].y);
	text_color(0, 10);
	cout << "O";
}
void DrawGate(int x, int y)
{
	TYPE = Random(1, 4); // Random 4 types of gates

	switch (TYPE)
	{
	case 1:
		DrawGateU1(x, y, "o");
		break;
	case 2:
		DrawGateU2(x, y, "o");
		break;
	case 3:
		DrawGateU3(x, y, "o");
		break;
	case 4:
		DrawGateU4(x, y, "o");
		break;
	}

	GateDraw = true; // Gate exits
}
void DrawGateU1(int x, int y, const string& st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x + i, y);
		Gate[cntGate++] = { x + i, y }; // Save coordinates of each point from gate to array
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x - 1, y - 1);
	Gate[cntGate++] = { x - 1, y - 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x + 1, y - 1);
	Gate[cntGate++] = { x + 1, y - 1 };
	text_color(0, 4);
	cout << st;
}
void DrawGateU2(int x, int y, const string& st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x + i, y);
		Gate[cntGate++] = { x + i, y };
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x - 1, y + 1);
	Gate[cntGate++] = { x - 1, y + 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x + 1, y + 1);
	Gate[cntGate++] = { x + 1, y + 1 };
	text_color(0, 4);
	cout << st;
}
void DrawGateU3(int x, int y, const string& st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x, y + i);
		Gate[cntGate++] = { x, y + i };
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x + 1, y - 1);
	Gate[cntGate++] = { x + 1, y - 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x + 1, y + 1);
	Gate[cntGate++] = { x + 1, y + 1 };
	text_color(0, 4);
	cout << st;
}
void DrawGateU4(int x, int y, const string& st)
{
	for (int i = -1; i <= 1; i++)
	{
		GotoXY(x, y + i);
		Gate[cntGate++] = { x, y + i };
		text_color(0, 4);
		cout << st;
	}

	GotoXY(x - 1, y - 1);
	Gate[cntGate++] = { x - 1, y - 1 };
	text_color(0, 4);
	cout << st;

	GotoXY(x - 1, y + 1);
	Gate[cntGate++] = { x - 1, y + 1 };
	text_color(0, 4);
	cout << st;
}

void ProcessGate(int &lev)
{
	if (GateDraw == false) // If doesn't meet the conditions to create Gate -> continue draw food to eat food 
	{
		DrawFood(); // (4 foods each level to create Gate)
	}
	else // Create Gate already
	{
		if (TouchGate()) // When come into gate and crash it -> DEAD
		{
			ProcessDead();
			return;
		}

		if (Snake[0].x == Center.x && Snake[0].y == Center.y && Snake_Size > 0) // Snake come into gate
		{
			for (int i = 0; i < Snake_Size - 1; i++)
				Snake[i] = Snake[i + 1];

			Snake_Size--;
		}

		if (Snake_Size == 0) // When all the body of snake come into Gate -> Erase Gate and move to next level
		{
			// Erase Gate
			EraseGate();
			GateDraw = false;

			DeltaSpeed += 0.05F; // Increase speed when move to next level
			lev++; // Move to next level

			if (lev == MAX_LEVEL)
			{
				ProcessWin();
				WIN = TRUE;
				return;
			}

			ResetData(); // Intialize original data when move to new level
			LoadGame(lev);
		}
	}
}
void EraseGate()
{
	for (int i = 0; i < cntGate; i++)
	{
		GotoXY(Gate[i].x, Gate[i].y);
		cout << " ";
	}
}
void EraseOldSnake()
{
	for (int i = 0; i < Snake_Size; i++)
	{
		GotoXY(Snake[i].x, Snake[i].y);
		text_color(0, 10);
		cout << " ";
		text_color(0, 7);
	}
}

bool isValidFood(int x, int y)
{
	for (int i = 0; i < Snake_Size; i++)
		if (Snake[i].x == x && Snake[i].y == y)
			return false;

	for (int i = 0; i < cntGate; i++)
		if (x == Gate[i].x && y == Gate[i].y)
			return false;

	for (int i = 0; i < obs_nums; i++)
		if (obs[i].x == x && obs[i].y == y)
			return false;
	return true;
}

void GenerateFood()
{
	int x, y;
	for (int i = 0; i < MAX_SIZE_FOOD; i++)
	{
		while (true)
		{
			x = Random(10, WIDTH_GAME - 10);
			y = Random(10, HEIGH_GAME - 10);

			if (isValidFood(x, y) == true)
			{
				bool check = true;

				for (int i = 0; i < obs_nums; i++)
					if (abs(obs[i].x - x) <= 2 && abs(obs[i].y - y) <= 2)
						check = false;

				if (GateDraw == true)
					check = false;

				if (check == true)
					break;
			}
		}

		Food[i] = { x, y }; // Random coordinates of food into array
	}
}
void EatFood()
{
	SCORE += 50;
	draw_matchBoard(x_pos, y_pos, HEIGHT_BOARD, WIDTH_BOARD, SCORE, LEVEL, 2, 0, "", 1);

	Snake[Snake_Size] = Food[ID_Food]; // Insert new size of body (Insert food coordinates)

	if (ID_Food == MAX_SIZE_FOOD - 1) // 4 foods can generate Gate
	{
		GenerateCenterGate();
		DrawGate(Center.x, Center.y); // Draw Gate
	}
	else // Increase size of snake, index of food
	{
		ID_Food++;
		Snake_Size++;
		GenerateFood();
	}
}

void GenerateCenterGate()
{
	int x, y;
	do
	{
		x = Random(8, WIDTH_GAME - 8);
		y = Random(8, HEIGH_GAME - 8);
	} while (CenterGate(x - 2, y) == false || CenterGate(x, y) == false || CenterGate(x + 2, y) == false
		|| CenterGate(x - 2, y - 2) == false || CenterGate(x, y - 2) == false || CenterGate(x + 2, y - 2) == false
		|| CenterGate(x - 2, y + 2) == false || CenterGate(x, y + 2) == false || CenterGate(x + 2, y + 2) == false);

	// Check 7x7 matrix with center is Center Point Of Gate (avoid gate opposite the bound)
	// It makes sure that there are no Food, Obstacles and Snake in this 7x7 matrix

	Center = { x, y };
}

// 8 directions from point (x, y) 
int dx[] = { -1, 0, 0, 1, -1, -1, 1, 1 };
int dy[] = { 0, -1, 1, 0, -1, 1, -1, 1 };

bool CenterGate(int x, int y)
{
	if (TouchWall(x, y) == true)
		return false;

	/*if (isValidFood(x, y) == true)
		return false;*/

	if (TouchObs(x, y) == true)
		return false;

	for (int dir = 0; dir < 8; dir++) // Check 8 directions from Center Point of Gate (Not food, obstacles, snake, wall)
	{
		int new_x = x + dx[dir];
		int new_y = y + dy[dir];

		if (TouchWall(new_x, new_y) == true)
			return false;

		/*if (isValidFood(new_x, new_y) == true)
			return false;*/

		if (TouchObs(new_x, new_y) == true)
			return false;

		for (int i = 0; i < obs_nums; i++)
			if (abs(obs[i].x - new_x) <= 1 && abs(obs[i].y - new_y) <= 1)
				return false;
	}

	return true;
}

bool TouchWall(int x, int y)
{
	return !(x > 1 && x < WIDTH_GAME && y > 3 && y < HEIGH_GAME);
}
bool TouchItself()
{
	for (int i = 1; i < Snake_Size; i++)
		if (Snake[i].x == Snake[0].x && Snake[i].y == Snake[0].y)
			return true;

	return false;
}
bool TouchObs(int x, int y)
{
	for (int i = 0; i < obs_nums; i++)
		if (x == obs[i].x && y == obs[i].y)
			return true;

	return false;
}

bool TouchGate()
{
	for (int i = 0; i < cntGate; i++)
	{
		if (Gate[i].x == Center.x && Gate[i].y == Center.y)
		{
			if (Snake[0].x == Gate[i].x && Snake[0].y == Gate[i].y)
			{
				// Check that snake come into Gate with right direction
				if (TYPE == 1) // Gate type 1
					return !(MOVING == 'S' || MOVING == 'P');

				if (TYPE == 2) // Gate type 2
					return !(MOVING == 'W' || MOVING == 'H');

				if (TYPE == 3) // Gate type 3
					return !(MOVING == 'A' || MOVING == 'K');

				if (TYPE == 4) // Gate type 4
					return !(MOVING == 'D' || MOVING == 'M');
			}

			for (int j = 1; j < Snake_Size; j++)
			{
				if (Snake[j].x == Gate[i].x && Snake[j].y == Gate[i].y)
					return true;
			}
		}
		else
		{
			for (int j = 0; j < Snake_Size; j++)
			{
				if (Snake[j].x == Gate[i].x && Snake[j].y == Gate[i].y)
					return true;
			}
		}
	}

	return false;
}

void MoveUp()
{
	if (TouchWall(Snake[0].x, Snake[0].y - 1) == true || TouchObs(Snake[0].x, Snake[0].y - 1) == true) // Touch the Wall or Obstacle -> You lose
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x == Food[ID_Food].x && Snake[0].y - 1 == Food[ID_Food].y) // If move to coordinates of Food -> Eat Food
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--) // Change the coordinates of Snake
		Snake[i + 1] = Snake[i];

	Snake[0].y--; // Move up

	if (TouchItself() || TouchGate() || WIN == true) // Check conditions to make sure that snake still ALIVE
	{
		ProcessDead();
		return;
	}
}
void MoveDown()
{
	if (TouchWall(Snake[0].x, Snake[0].y + 1) == true || TouchObs(Snake[0].x, Snake[0].y + 1) == true)
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x == Food[ID_Food].x && Snake[0].y + 1 == Food[ID_Food].y)
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--)
		Snake[i + 1] = Snake[i];

	Snake[0].y++; // Move down

	if (TouchItself() || TouchGate() || WIN == true)
	{
		ProcessDead();
		return;
	}
}
void MoveRight()
{
	if (TouchWall(Snake[0].x + 1, Snake[0].y) == true || TouchObs(Snake[0].x + 1, Snake[0].y) == true)
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x + 1 == Food[ID_Food].x && Snake[0].y == Food[ID_Food].y)
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--)
		Snake[i + 1] = Snake[i];

	Snake[0].x++; // Move right

	if (TouchItself() || TouchGate() || WIN == true)
	{
		ProcessDead();
		return;
	}
}
void MoveLeft()
{
	if (TouchWall(Snake[0].x - 1, Snake[0].y) == true || TouchObs(Snake[0].x - 1, Snake[0].y) == true)
	{
		ProcessDead();
		return;
	}

	if (Snake[0].x - 1 == Food[ID_Food].x && Snake[0].y == Food[ID_Food].y)
		EatFood();

	for (int i = Snake_Size - 2; i >= 0; i--)
		Snake[i + 1] = Snake[i];

	Snake[0].x--; // Move left

	if (TouchItself() || TouchGate() || WIN == true)
	{
		ProcessDead();
		return;
	}
}

