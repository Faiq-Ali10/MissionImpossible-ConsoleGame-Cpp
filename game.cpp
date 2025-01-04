#include <iostream>
#include <conio.h>
#include<cstdlib>
#include <windows.h>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

//Prototypes
int const Row_Size = 30, Col_Size = 50;
void move_robot(char map[][Col_Size]);
int random_range();
void update_robot(int n, char map[][Col_Size]);
void fire_bullet(char map[][Col_Size], char direction);
void start_robot(int& r1, int& r2, int& c1, int& c2, int& c3, char map[][Col_Size]);
bool isValid_robot(int& r1, int& r2, int& c1, int& c2, int& c3, char map[][Col_Size]);
bool check_collision(int r1a, int r2a, int c1a, int c2a, int c3a, int r1b, int r2b, int c1b, int c2b, int c3b);
bool check_robot_collision(int n);
void is_robot_update(int& r1, int& r2, int& c1, int& c2, int& c3, char map[][Col_Size], char move, int n);
void handle_high_scores(const string& currentName, int score);
void update_solo();
void move_solo(char map[][Col_Size], int steps);

//Ethan variable
int prev_top_r = 24, prev_top_c = 25, prev_mid_r = 25, prev_mid1_c = 24, prev_mid2_c = 25,
prev_mid3_c = 26, prev_bottom_r = 26, prev_bottom1_c = 24, prev_bottom2_c = 26;

// Soloman variable
int solo_r = -1, solo_c = -1;

//Robot variable
// Robot1
int robot1_r1;
int robot1_r2;
int robot1_c1;
int robot1_c2;
int robot1_c3;
//Robot2
int robot2_r1;
int robot2_r2;
int robot2_c1;
int robot2_c2;
int robot2_c3;
//Robot3
int robot3_r1;
int robot3_r2;
int robot3_c1;
int robot3_c2;
int robot3_c3;
//Robot4
int robot4_r1;
int robot4_r2;
int robot4_c1;
int robot4_c2;
int robot4_c3;
//Robot5
int robot5_r1;
int robot5_r2;
int robot5_c1;
int robot5_c2;
int robot5_c3;
//Robot6
int robot6_r1;
int robot6_r2;
int robot6_c1;
int robot6_c2;
int robot6_c3;

//Level of game
int LEVEL = 1;
//score
int SCORE = 0;
//for lives
int ethan_lives = 3;
//for file handling (topscorers)
fstream file;

// Functions
void initialize_map(char map[][Col_Size])
{
	for (int i = 0; i < Row_Size; i++)
	{
		for (int j = 0; j < Col_Size; j++)
		{
			if (i == 0 || i == Row_Size - 1)
			{
				map[i][j] = '-';
			}
			else if (j == 0 || j == Col_Size - 1)
			{
				map[i][j] = '|';
			}
			else
			{
				map[i][j] = ' ';
			}
		}

	}
	for (int k = 16; k <= 30; k++)
	{
		map[0][k] = ' ';
	}
}

void print_map(char map[][Col_Size])
{ //Ethan
	map[prev_top_r][prev_top_c] = '0';
	map[prev_mid_r][prev_mid1_c] = '/';
	map[prev_mid_r][prev_mid2_c] = '|';
	map[prev_mid_r][prev_mid3_c] = '\\';
	map[prev_bottom_r][prev_bottom1_c] = '/';
	map[prev_bottom_r][prev_bottom2_c] = '\\';

	switch (LEVEL)
	{
	case 1:
		// Obstcaless
		map[10][23] = '[';
		map[10][24] = '-';
		map[10][25] = '-';
		map[10][26] = '-';
		map[10][27] = ']';

		map[20][23] = '[';
		map[20][24] = '-';
		map[20][25] = '-';
		map[20][26] = '-';
		map[20][27] = ']';

		// Robots
		map[robot1_r1][robot1_c1] = '[';
		map[robot1_r1][robot1_c2] = '|';
		map[robot1_r1][robot1_c3] = ']';
		map[robot1_r2][robot1_c1] = '[';
		map[robot1_r2][robot1_c2] = 'V';
		map[robot1_r2][robot1_c3] = ']';

		map[robot2_r1][robot2_c1] = '[';
		map[robot2_r1][robot2_c2] = '|';
		map[robot2_r1][robot2_c3] = ']';
		map[robot2_r2][robot2_c1] = '[';
		map[robot2_r2][robot2_c2] = 'V';
		map[robot2_r2][robot2_c3] = ']';

		break;



	case 2:
		map[10][5] = '[';
		map[10][6] = '-';
		map[10][7] = '-';
		map[10][8] = '-';
		map[10][9] = ']';

		map[10][40] = '[';
		map[10][41] = '-';
		map[10][42] = '-';
		map[10][43] = '-';
		map[10][44] = ']';

		map[20][23] = '[';
		map[20][24] = '-';
		map[20][25] = '-';
		map[20][26] = '-';
		map[20][27] = ']';

		// Robots
		map[robot1_r1][robot1_c1] = '[';
		map[robot1_r1][robot1_c2] = '|';
		map[robot1_r1][robot1_c3] = ']';
		map[robot1_r2][robot1_c1] = '[';
		map[robot1_r2][robot1_c2] = 'V';
		map[robot1_r2][robot1_c3] = ']';

		map[robot2_r1][robot2_c1] = '[';
		map[robot2_r1][robot2_c2] = '|';
		map[robot2_r1][robot2_c3] = ']';
		map[robot2_r2][robot2_c1] = '[';
		map[robot2_r2][robot2_c2] = 'V';
		map[robot2_r2][robot2_c3] = ']';

		map[robot3_r1][robot3_c1] = '[';
		map[robot3_r1][robot3_c2] = '|';
		map[robot3_r1][robot3_c3] = ']';
		map[robot3_r2][robot3_c1] = '[';
		map[robot3_r2][robot3_c2] = 'V';
		map[robot3_r2][robot3_c3] = ']';

		break;

	case 3:
		map[10][5] = '[';
		map[10][6] = '-';
		map[10][7] = '-';
		map[10][8] = '-';
		map[10][9] = '-';
		map[10][10] = ']';

		map[10][40] = '[';
		map[10][41] = '-';
		map[10][42] = '-';
		map[10][43] = '-';
		map[10][44] = '-';
		map[10][45] = ']';

		map[20][23] = '[';
		map[20][24] = '-';
		map[20][25] = '-';
		map[20][26] = '-';
		map[20][27] = '-';
		map[20][28] = ']';

		// Robots
		map[robot1_r1][robot1_c1] = '[';
		map[robot1_r1][robot1_c2] = '|';
		map[robot1_r1][robot1_c3] = ']';
		map[robot1_r2][robot1_c1] = '[';
		map[robot1_r2][robot1_c2] = 'V';
		map[robot1_r2][robot1_c3] = ']';

		map[robot2_r1][robot2_c1] = '[';
		map[robot2_r1][robot2_c2] = '|';
		map[robot2_r1][robot2_c3] = ']';
		map[robot2_r2][robot2_c1] = '[';
		map[robot2_r2][robot2_c2] = 'V';
		map[robot2_r2][robot2_c3] = ']';

		map[robot3_r1][robot3_c1] = '[';
		map[robot3_r1][robot3_c2] = '|';
		map[robot3_r1][robot3_c3] = ']';
		map[robot3_r2][robot3_c1] = '[';
		map[robot3_r2][robot3_c2] = 'V';
		map[robot3_r2][robot3_c3] = ']';

		map[robot4_r1][robot4_c1] = '[';
		map[robot4_r1][robot4_c2] = '|';
		map[robot4_r1][robot4_c3] = ']';
		map[robot4_r2][robot4_c1] = '[';
		map[robot4_r2][robot4_c2] = 'V';
		map[robot4_r2][robot4_c3] = ']';

		break;

	case 4:
		map[5][23] = '[';
		map[5][24] = '-';
		map[5][25] = '-';
		map[5][26] = '-';
		map[5][27] = '-';
		map[5][28] = ']';

		map[10][5] = '[';
		map[10][6] = '-';
		map[10][7] = '-';
		map[10][8] = '-';
		map[10][9] = '-';
		map[10][10] = ']';

		map[10][40] = '[';
		map[10][41] = '-';
		map[10][42] = '-';
		map[10][43] = '-';
		map[10][44] = '-';
		map[10][45] = ']';

		map[20][23] = '[';
		map[20][24] = '-';
		map[20][25] = '-';
		map[20][26] = '-';
		map[20][27] = '-';
		map[20][28] = ']';

		// Robots
		map[robot1_r1][robot1_c1] = '[';
		map[robot1_r1][robot1_c2] = '|';
		map[robot1_r1][robot1_c3] = ']';
		map[robot1_r2][robot1_c1] = '[';
		map[robot1_r2][robot1_c2] = 'V';
		map[robot1_r2][robot1_c3] = ']';

		map[robot2_r1][robot2_c1] = '[';
		map[robot2_r1][robot2_c2] = '|';
		map[robot2_r1][robot2_c3] = ']';
		map[robot2_r2][robot2_c1] = '[';
		map[robot2_r2][robot2_c2] = 'V';
		map[robot2_r2][robot2_c3] = ']';

		map[robot3_r1][robot3_c1] = '[';
		map[robot3_r1][robot3_c2] = '|';
		map[robot3_r1][robot3_c3] = ']';
		map[robot3_r2][robot3_c1] = '[';
		map[robot3_r2][robot3_c2] = 'V';
		map[robot3_r2][robot3_c3] = ']';

		map[robot4_r1][robot4_c1] = '[';
		map[robot4_r1][robot4_c2] = '|';
		map[robot4_r1][robot4_c3] = ']';
		map[robot4_r2][robot4_c1] = '[';
		map[robot4_r2][robot4_c2] = 'V';
		map[robot4_r2][robot4_c3] = ']';

		map[robot5_r1][robot5_c1] = '[';
		map[robot5_r1][robot5_c2] = '|';
		map[robot5_r1][robot5_c3] = ']';
		map[robot5_r2][robot5_c1] = '[';
		map[robot5_r2][robot5_c2] = 'V';
		map[robot5_r2][robot5_c3] = ']';

		break;

	case 5:
		map[5][5] = '[';
		map[5][6] = '-';
		map[5][7] = '-';
		map[5][8] = '-';
		map[5][9] = '-';
		map[5][10] = '-';
		map[5][11] = ']';

		map[5][40] = '[';
		map[5][41] = '-';
		map[5][42] = '-';
		map[5][43] = '-';
		map[5][44] = '-';
		map[5][45] = '-';
		map[5][46] = ']';

		map[13][23] = '[';
		map[13][24] = '-';
		map[13][25] = '-';
		map[13][26] = '-';
		map[13][27] = '-';
		map[13][28] = '-';
		map[13][29] = ']';

		map[20][5] = '[';
		map[20][6] = '-';
		map[20][7] = '-';
		map[20][8] = '-';
		map[20][9] = '-';
		map[20][10] = '-';
		map[20][11] = ']';

		map[20][40] = '[';
		map[20][41] = '-';
		map[20][42] = '-';
		map[20][43] = '-';
		map[20][44] = '-';
		map[20][45] = '-';
		map[20][46] = ']';

		// Robots
		map[robot1_r1][robot1_c1] = '[';
		map[robot1_r1][robot1_c2] = '|';
		map[robot1_r1][robot1_c3] = ']';
		map[robot1_r2][robot1_c1] = '[';
		map[robot1_r2][robot1_c2] = 'V';
		map[robot1_r2][robot1_c3] = ']';

		map[robot2_r1][robot2_c1] = '[';
		map[robot2_r1][robot2_c2] = '|';
		map[robot2_r1][robot2_c3] = ']';
		map[robot2_r2][robot2_c1] = '[';
		map[robot2_r2][robot2_c2] = 'V';
		map[robot2_r2][robot2_c3] = ']';

		map[robot3_r1][robot3_c1] = '[';
		map[robot3_r1][robot3_c2] = '|';
		map[robot3_r1][robot3_c3] = ']';
		map[robot3_r2][robot3_c1] = '[';
		map[robot3_r2][robot3_c2] = 'V';
		map[robot3_r2][robot3_c3] = ']';

		map[robot4_r1][robot4_c1] = '[';
		map[robot4_r1][robot4_c2] = '|';
		map[robot4_r1][robot4_c3] = ']';
		map[robot4_r2][robot4_c1] = '[';
		map[robot4_r2][robot4_c2] = 'V';
		map[robot4_r2][robot4_c3] = ']';

		map[robot5_r1][robot5_c1] = '[';
		map[robot5_r1][robot5_c2] = '|';
		map[robot5_r1][robot5_c3] = ']';
		map[robot5_r2][robot5_c1] = '[';
		map[robot5_r2][robot5_c2] = 'V';
		map[robot5_r2][robot5_c3] = ']';

		map[robot6_r1][robot6_c1] = '[';
		map[robot6_r1][robot6_c2] = '|';
		map[robot6_r1][robot6_c3] = ']';
		map[robot6_r2][robot6_c1] = '[';
		map[robot6_r2][robot6_c2] = 'V';
		map[robot6_r2][robot6_c3] = ']';

		break;
	}
	if (solo_c > 0 && solo_r > 0)
	{
		//Soloman
		map[solo_r][solo_c] = 'X';
		map[solo_r - 1][solo_c - 1] = '[';
		map[solo_r - 1][solo_c + 1] = ']';
		map[solo_r + 1][solo_c - 1] = '[';
		map[solo_r + 1][solo_c + 1] = ']';
		map[solo_r][solo_c - 1] = '[';
		map[solo_r][solo_c - 2] = ']';
		map[solo_r][solo_c - 3] = '[';
		map[solo_r][solo_c + 1] = ']';
		map[solo_r][solo_c + 2] = '[';
		map[solo_r][solo_c + 3] = ']';
	}

	for (int i = 0; i < Row_Size; i++)
	{
		for (int j = 0; j < Col_Size; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

void move_solo(char map[][Col_Size], int steps)
{
	// Clear Solo's previous position
	map[solo_r][solo_c] = ' ';
	map[solo_r - 1][solo_c - 1] = ' ';
	map[solo_r - 1][solo_c + 1] = ' ';
	map[solo_r + 1][solo_c - 1] = ' ';
	map[solo_r + 1][solo_c + 1] = ' ';
	map[solo_r][solo_c - 1] = ' ';
	map[solo_r][solo_c - 2] = ' ';
	map[solo_r][solo_c - 3] = ' ';
	map[solo_r][solo_c + 1] = ' ';
	map[solo_r][solo_c + 2] = ' ';
	map[solo_r][solo_c + 3] = ' ';

	// Move Solo randomly
	int n = rand() % 4;
	switch (n)
	{
	case 0:
		solo_r += steps + 1;
		if (solo_r > 26) solo_r -= steps + 1;
		break;
	case 1:
		solo_r -= steps + 1;
		if (solo_r < 3) solo_r += steps + 1;
		break;
	case 2:
		solo_c += steps + 1;
		if (solo_c > 45) solo_c -= steps + 1;
		break;
	case 3:
		solo_c -= steps + 1;
		if (solo_c < 5) solo_c += steps + 1;
		break;
	}
}

void update_solo()
{
	solo_r = random_range() + 3;
	solo_c = random_range() + 4;
}

bool isValid_robot(int& r1, int& r2, int& c1, int& c2, int& c3, char map[][Col_Size])
{
	if (map[r1][c1] == '[' || map[r1][c1] == '-' || map[r1][c1] == ']' || map[r1][c1] == 'V' ||
		map[r1][c3] == '[' || map[r1][c3] == '-' || map[r1][c3] == ']' || map[r1][c3] == 'V' ||
		map[r2][c1] == '[' || map[r2][c1] == '-' || map[r2][c1] == ']' || map[r2][c1] == '|' ||
		map[r2][c3] == '[' || map[r2][c3] == '-' || map[r2][c3] == ']' || map[r2][c3] == '|')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void start_robot(int& r1, int& r2, int& c1, int& c2, int& c3, char map[][Col_Size])
{
	r1 = random_range();
	r2 = r1 + 1;
	c1 = random_range();
	c2 = c1 + 1;
	c3 = c2 + 1;

	while (!(isValid_robot(r1, r2, c1, c2, c3, map)))
	{
		r1 = random_range();
		r2 = r1 + 1;
		c1 = random_range();
		c2 = c1 + 1;
		c3 = c2 + 1;
	}
}

void update_robot(int n, char map[][Col_Size])
{

	switch (n)
	{
	case 1:
		start_robot(robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3, map);
		break;


	case 2:
		start_robot(robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3, map);
		break;

	case 3:
		start_robot(robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3, map);
		break;

	case 4:
		start_robot(robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3, map);
		break;

	case 5:
		start_robot(robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3, map);
		break;

	case 6:
		start_robot(robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3, map);
		break;
	}

}



void move_ethan(char map[][Col_Size], char mov)
{
	map[prev_top_r][prev_top_c] = ' ';
	map[prev_mid_r][prev_mid1_c] = ' ';
	map[prev_mid_r][prev_mid2_c] = ' ';
	map[prev_mid_r][prev_mid3_c] = ' ';
	map[prev_bottom_r][prev_bottom1_c] = ' ';
	map[prev_bottom_r][prev_bottom2_c] = ' ';

	move_robot(map);
	move_solo(map, LEVEL);

	switch (mov)
	{
	case 72:
		prev_top_r -= 1;
		prev_mid_r -= 1;
		prev_bottom_r -= 1;
		break;
	case 80:
		prev_top_r += 1;
		prev_mid_r += 1;
		prev_bottom_r += 1;
		break;
	case 75:
		prev_top_c -= 1;
		prev_mid1_c -= 1;
		prev_mid2_c -= 1;
		prev_mid3_c -= 1;
		prev_bottom1_c -= 1;
		prev_bottom2_c -= 1;
		break;
	case 77:
		prev_top_c += 1;
		prev_mid1_c += 1;
		prev_mid2_c += 1;
		prev_mid3_c += 1;
		prev_bottom1_c += 1;
		prev_bottom2_c += 1;
		break;

	}

	if (map[prev_top_r][prev_top_c] == '-' || map[prev_top_r][prev_top_c] == '[' ||
		map[prev_top_r][prev_top_c] == ']')
	{
		prev_top_r += 2;
		prev_mid_r += 2;
		prev_bottom_r += 2;
	}
	else if (map[prev_bottom_r][prev_bottom1_c] == '-' || map[prev_bottom_r][prev_bottom1_c] == '[' ||
		map[prev_bottom_r][prev_bottom1_c] == ']' || map[prev_bottom_r][prev_bottom2_c] == '-' || map[prev_bottom_r][prev_bottom2_c] == '[' ||
		map[prev_bottom_r][prev_bottom2_c] == ']')
	{
		prev_bottom_r -= 2;
		prev_top_r -= 2;
		prev_mid_r -= 2;
	}
	else if (map[prev_mid_r][prev_mid1_c] == '|' || map[prev_mid_r][prev_mid1_c] == ']' ||
		map[prev_bottom_r][prev_mid1_c] == ']')
	{
		prev_top_c += 2;
		prev_mid1_c += 2;
		prev_mid2_c += 2;
		prev_mid3_c += 2;
		prev_bottom1_c += 2;
		prev_bottom2_c += 2;
	}
	else if (map[prev_mid_r][prev_mid3_c] == '|' || map[prev_mid_r][prev_mid3_c] == '[' || map[prev_bottom_r][prev_mid3_c] == '[')
	{
		prev_top_c -= 2;
		prev_mid1_c -= 2;
		prev_mid2_c -= 2;
		prev_mid3_c -= 2;
		prev_bottom1_c -= 2;
		prev_bottom2_c -= 2;
	}

}

int random_range()
{
	return rand() % (20 - 2) + 2;
}

bool check_collision(int r1a, int r2a, int c1a, int c2a, int c3a, int r1b, int r2b, int c1b, int c2b, int c3b)
{
	return
		(r1a == r1b && (c1a == c1b || c1a == c2b || c1a == c3b)) || // Part 1 of A with parts of B
		(r1a == r2b && (c1a == c1b || c1a == c2b || c1a == c3b)) || // Part 1 of A with parts of B (different row)
		(r2a == r1b && (c2a == c1b || c2a == c2b || c2a == c3b)) || // Part 2 of A with parts of B
		(r2a == r2b && (c2a == c1b || c2a == c2b || c2a == c3b)) || // Part 2 of A with parts of B (same row)
		(r1a == r1b && (c3a == c1b || c3a == c2b || c3a == c3b)) || // Part 3 of A with parts of B
		(r1a == r2b && (c3a == c1b || c3a == c2b || c3a == c3b)) || // Part 3 of A with parts of B (different row)
		(r2a == r1b && (c3a == c1b || c3a == c2b || c3a == c3b)) || // Part 3 of A with parts of B
		(r2a == r2b && (c3a == c1b || c3a == c2b || c3a == c3b));
}

bool check_robot_collision(int n)
{
	switch (n)
	{
	case 1:
		if (check_collision(robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3,
			robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3) ||
			check_collision(robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3,
				robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3) ||
			check_collision(robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3,
				robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3) ||
			check_collision(robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3,
				robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3) ||
			check_collision(robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3,
				robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 2:
		if (check_collision(robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3,
			robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3) ||
			check_collision(robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3,
				robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3) ||
			check_collision(robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3,
				robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3) ||
			check_collision(robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3,
				robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3) ||
			check_collision(robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3,
				robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 3:
		if (check_collision(robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3,
			robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3) ||
			check_collision(robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3,
				robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3) ||
			check_collision(robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3,
				robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3) ||
			check_collision(robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3,
				robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3) ||
			check_collision(robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3,
				robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 4:
		if (check_collision(robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3,
			robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3) ||
			check_collision(robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3,
				robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3) ||
			check_collision(robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3,
				robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3) ||
			check_collision(robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3,
				robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3) ||
			check_collision(robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3,
				robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 5:
		if (check_collision(robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3,
			robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3) ||
			check_collision(robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3,
				robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3) ||
			check_collision(robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3,
				robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3) ||
			check_collision(robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3,
				robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3) ||
			check_collision(robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3,
				robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	case 6:
		if (check_collision(robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3,
			robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3) ||
			check_collision(robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3,
				robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3) ||
			check_collision(robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3,
				robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3) ||
			check_collision(robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3,
				robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3) ||
			check_collision(robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3,
				robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
}

void is_robot_update(int& r1, int& r2, int& c1, int& c2, int& c3, char map[][Col_Size], char move, int n)
{
	if (check_robot_collision(n))
	{
		switch (move)
		{
		case 'u':
			r1 += 1;
			r2 += 1;
			break;

		case 'd':
			r1 -= 1;
			r2 -= 1;
			break;

		case 'r':
			c1 -= 1;
			c2 -= 1;
			c3 -= 1;
			break;

		case 'l':
			c1 += 1;
			c2 += 1;
			c3 += 1;
			break;
		}
	}
	move = 'a';
}


void move_robot(char map[][Col_Size])
{
	char move = 'a';
	if (robot1_r1 > 0)
	{
		map[robot1_r1][robot1_c1] = ' ';
		map[robot1_r1][robot1_c2] = ' ';
		map[robot1_r1][robot1_c3] = ' ';
		map[robot1_r2][robot1_c1] = ' ';
		map[robot1_r2][robot1_c2] = ' ';
		map[robot1_r2][robot1_c3] = ' ';

		if (prev_top_r > robot1_r2 + 3)
		{
			move = 'd';
		}
		else if (prev_bottom_r + 4 < robot1_r1)
		{
			move = 'u';
		}
		else if (prev_mid1_c > robot1_c2 + 4)
		{
			move = 'r';
		}
		else if (prev_mid3_c + 4 < robot1_c1)
		{
			move = 'l';
		}

		switch (move)
		{
		case 'u':
			robot1_r1 -= 1;
			robot1_r2 -= 1;
			break;

		case 'd':
			robot1_r1 += 1;
			robot1_r2 += 1;
			break;

		case 'r':
			robot1_c1 += 1;
			robot1_c2 += 1;
			robot1_c3 += 1;
			break;

		case 'l':
			robot1_c1 -= 1;
			robot1_c2 -= 1;
			robot1_c3 -= 1;
			break;

		}
		is_robot_update(robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3, map, move, 1);
	}

	if (robot2_r1 > 0)
	{
		map[robot2_r1][robot2_c1] = ' ';
		map[robot2_r1][robot2_c2] = ' ';
		map[robot2_r1][robot2_c3] = ' ';
		map[robot2_r2][robot2_c1] = ' ';
		map[robot2_r2][robot2_c2] = ' ';
		map[robot2_r2][robot2_c3] = ' ';

		if (prev_top_r > robot2_r2 + 4)
		{
			move = 'd';
		}
		else if (prev_bottom_r + 4 < robot2_r1)
		{
			move = 'u';
		}
		else if (prev_mid1_c > robot2_c2 + 4)
		{
			move = 'r';
		}
		else if (prev_mid3_c + 4 < robot2_c1)
		{
			move = 'l';
		}

		switch (move)
		{
		case 'u':
			robot2_r1 -= 1;
			robot2_r2 -= 1;
			break;

		case 'd':
			robot2_r1 += 1;
			robot2_r2 += 1;
			break;

		case 'r':
			robot2_c1 += 1;
			robot2_c2 += 1;
			robot2_c3 += 1;
			break;

		case 'l':
			robot2_c1 -= 1;
			robot2_c2 -= 1;
			robot2_c3 -= 1;
			break;
		}
		is_robot_update(robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3, map, move, 2);
	}

	if (robot3_r1 > 0)
	{
		map[robot3_r1][robot3_c1] = ' ';
		map[robot3_r1][robot3_c2] = ' ';
		map[robot3_r1][robot3_c3] = ' ';
		map[robot3_r2][robot3_c1] = ' ';
		map[robot3_r2][robot3_c2] = ' ';
		map[robot3_r2][robot3_c3] = ' ';

		if (prev_top_r > robot3_r2 + 4)
		{
			move = 'd';
		}
		else if (prev_bottom_r + 4 < robot3_r1)
		{
			move = 'u';
		}
		else if (prev_mid1_c > robot3_c2 + 4)
		{
			move = 'r';
		}
		else if (prev_mid3_c + 4 < robot3_c1)
		{
			move = 'l';
		}

		switch (move)
		{
		case 'u':
			robot3_r1 -= 1;
			robot3_r2 -= 1;
			break;

		case 'd':
			robot3_r1 += 1;
			robot3_r2 += 1;
			break;

		case 'r':
			robot3_c1 += 1;
			robot3_c2 += 1;
			robot3_c3 += 1;
			break;

		case 'l':
			robot3_c1 -= 1;
			robot3_c2 -= 1;
			robot3_c3 -= 1;
			break;
		}
		is_robot_update(robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3, map, move, 3);
	}

	if (robot4_r1 > 0)
	{
		map[robot4_r1][robot4_c1] = ' ';
		map[robot4_r1][robot4_c2] = ' ';
		map[robot4_r1][robot4_c3] = ' ';
		map[robot4_r2][robot4_c1] = ' ';
		map[robot4_r2][robot4_c2] = ' ';
		map[robot4_r2][robot4_c3] = ' ';

		if (prev_top_r > robot4_r2 + 4)
		{
			move = 'd';
		}
		else if (prev_bottom_r + 4 < robot4_r1)
		{
			move = 'u';
		}
		else if (prev_mid1_c > robot4_c2 + 4)
		{
			move = 'r';
		}
		else if (prev_mid3_c + 4 < robot4_c1)
		{
			move = 'l';
		}

		switch (move)
		{
		case 'u':
			robot4_r1 -= 1;
			robot4_r2 -= 1;
			break;

		case 'd':
			robot4_r1 += 1;
			robot4_r2 += 1;
			break;

		case 'r':
			robot4_c1 += 1;
			robot4_c2 += 1;
			robot4_c3 += 1;
			break;

		case 'l':
			robot4_c1 -= 1;
			robot4_c2 -= 1;
			robot4_c3 -= 1;
			break;
		}
		is_robot_update(robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3, map, move, 4);
	}

	if (robot5_r1 > 0)
	{
		map[robot5_r1][robot5_c1] = ' ';
		map[robot5_r1][robot5_c2] = ' ';
		map[robot5_r1][robot5_c3] = ' ';
		map[robot5_r2][robot5_c1] = ' ';
		map[robot5_r2][robot5_c2] = ' ';
		map[robot5_r2][robot5_c3] = ' ';

		if (prev_top_r > robot5_r2 + 4)
		{
			move = 'd';
		}
		else if (prev_bottom_r + 4 < robot5_r1)
		{
			move = 'u';
		}
		else if (prev_mid1_c > robot5_c2 + 4)
		{
			move = 'r';
		}
		else if (prev_mid3_c + 4 < robot5_c1)
		{
			move = 'l';
		}

		switch (move)
		{
		case 'u':
			robot5_r1 -= 1;
			robot5_r2 -= 1;
			break;

		case 'd':
			robot5_r1 += 1;
			robot5_r2 += 1;
			break;

		case 'r':
			robot5_c1 += 1;
			robot5_c2 += 1;
			robot5_c3 += 1;
			break;

		case 'l':
			robot5_c1 -= 1;
			robot5_c2 -= 1;
			robot5_c3 -= 1;
			break;
		}
		is_robot_update(robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3, map, move, 5);
	}

	if (robot6_r1 > 0)
	{
		map[robot6_r1][robot6_c1] = ' ';
		map[robot6_r1][robot6_c2] = ' ';
		map[robot6_r1][robot6_c3] = ' ';
		map[robot6_r2][robot6_c1] = ' ';
		map[robot6_r2][robot6_c2] = ' ';
		map[robot6_r2][robot6_c3] = ' ';

		if (prev_top_r > robot6_r2 + 4)
		{
			move = 'd';
		}
		else if (prev_bottom_r + 4 < robot6_r1)
		{
			move = 'u';
		}
		else if (prev_mid1_c > robot6_c2 + 4)
		{
			move = 'r';
		}
		else if (prev_mid3_c + 4 < robot6_c1)
		{
			move = 'l';
		}

		switch (move)
		{
		case 'u':
			robot6_r1 -= 1;
			robot6_r2 -= 1;
			break;

		case 'd':
			robot6_r1 += 1;
			robot6_r2 += 1;
			break;

		case 'r':
			robot6_c1 += 1;
			robot6_c2 += 1;
			robot6_c3 += 1;
			break;

		case 'l':
			robot6_c1 -= 1;
			robot6_c2 -= 1;
			robot6_c3 -= 1;
			break;
		}
		is_robot_update(robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3, map, move, 6);
	}

	if (!(robot1_r1 == -1) && (map[robot1_r1][robot1_c1] == '-' || map[robot1_r1][robot1_c1] == '[' || map[robot1_r1][robot1_c1] == ']' ||
		map[robot1_r1][robot1_c3] == '-' || map[robot1_r1][robot1_c3] == '[' || map[robot1_r1][robot1_c3] == ']' ||
		map[robot1_r2][robot1_c1] == '-' || map[robot1_r2][robot1_c1] == '[' || map[robot1_r2][robot1_c1] == ']' ||
		map[robot1_r2][robot1_c3] == '-' || map[robot1_r2][robot1_c3] == '[' || map[robot1_r2][robot1_c3] == ']'))
	{
		update_robot(1, map);
	}
	if (!(robot2_r1 == -1) && (map[robot2_r1][robot2_c1] == '-' || map[robot2_r1][robot2_c1] == '[' || map[robot2_r1][robot2_c1] == ']' ||
		map[robot2_r1][robot2_c3] == '-' || map[robot2_r1][robot2_c3] == '[' || map[robot2_r1][robot2_c3] == ']' ||
		map[robot2_r2][robot2_c1] == '-' || map[robot2_r2][robot2_c1] == '[' || map[robot2_r2][robot2_c1] == ']' ||
		map[robot2_r2][robot2_c3] == '-' || map[robot2_r2][robot2_c3] == '[' || map[robot2_r2][robot2_c3] == ']'))
	{
		update_robot(2, map);
	}
	if (!(robot3_r1 == -1) && (map[robot3_r1][robot3_c1] == '-' || map[robot3_r1][robot3_c1] == '[' || map[robot3_r1][robot3_c1] == ']' ||
		map[robot3_r1][robot3_c3] == '-' || map[robot3_r1][robot3_c3] == '[' || map[robot3_r1][robot3_c3] == ']' ||
		map[robot3_r2][robot3_c1] == '-' || map[robot3_r2][robot3_c1] == '[' || map[robot3_r2][robot3_c1] == ']' ||
		map[robot3_r2][robot3_c3] == '-' || map[robot3_r2][robot3_c3] == '[' || map[robot3_r2][robot3_c3] == ']'))
	{
		update_robot(3, map);
	}
	if (!(robot3_r1 == -1) && (map[robot4_r1][robot4_c1] == '-' || map[robot4_r1][robot4_c1] == '[' || map[robot4_r1][robot4_c1] == ']' ||
		map[robot4_r1][robot4_c3] == '-' || map[robot4_r1][robot4_c3] == '[' || map[robot4_r1][robot4_c3] == ']' ||
		map[robot4_r2][robot4_c1] == '-' || map[robot4_r2][robot4_c1] == '[' || map[robot4_r2][robot4_c1] == ']' ||
		map[robot4_r2][robot4_c3] == '-' || map[robot4_r2][robot4_c3] == '[' || map[robot4_r2][robot4_c3] == ']'))
	{
		update_robot(4, map);
	}
	if (!(robot4_r1 == -1) && (map[robot5_r1][robot5_c1] == '-' || map[robot5_r1][robot5_c1] == '[' || map[robot5_r1][robot5_c1] == ']' ||
		map[robot5_r1][robot5_c3] == '-' || map[robot5_r1][robot5_c3] == '[' || map[robot5_r1][robot5_c3] == ']' ||
		map[robot5_r2][robot5_c1] == '-' || map[robot5_r2][robot5_c1] == '[' || map[robot5_r2][robot5_c1] == ']' ||
		map[robot5_r2][robot5_c3] == '-' || map[robot5_r2][robot5_c3] == '[' || map[robot5_r2][robot5_c3] == ']'))
	{
		update_robot(5, map);
	}
	if (!(robot3_r1 == -1) && (map[robot6_r1][robot6_c1] == '-' || map[robot6_r1][robot6_c1] == '[' || map[robot6_r1][robot6_c1] == ']' ||
		map[robot6_r1][robot6_c3] == '-' || map[robot6_r1][robot6_c3] == '[' || map[robot6_r1][robot6_c3] == ']' ||
		map[robot6_r2][robot6_c1] == '-' || map[robot6_r2][robot6_c1] == '[' || map[robot6_r2][robot6_c1] == ']' ||
		map[robot6_r2][robot6_c3] == '-' || map[robot6_r2][robot6_c3] == '[' || map[robot6_r2][robot6_c3] == ']'))
	{
		update_robot(6, map);
	}
}

void remove_robot(char map[][Col_Size], int r1, int r2, int c1, int c2, int c3)// Clear all parts of the robot on the map
{
	SCORE = SCORE + 2;
	map[r1][c1] = ' ';
	map[r1][c2] = ' ';
	map[r1][c3] = ' ';
	map[r2][c1] = ' ';
	map[r2][c2] = ' ';
	map[r2][c3] = ' ';
}

void fire_bullet(char map[][Col_Size], char direction)
{
	int bullet_row = prev_mid_r;
	int bullet_col = prev_mid2_c;

	while (true) {
		// Move the bullet base on direction
		switch (direction)
		{
		case 'w':
			bullet_row--;
			break;
		case 's':
			bullet_row++;
			break;
		case 'a':
			bullet_col--;
			break;
		case 'd':
			bullet_col++;
			break;
		}

		// Check for Robot 1
		if ((bullet_row == robot1_r1 || bullet_row == robot1_r2) &&
			(bullet_col == robot1_c1 || bullet_col == robot1_c2 || bullet_col == robot1_c3))
		{
			remove_robot(map, robot1_r1, robot1_r2, robot1_c1, robot1_c2, robot1_c3);
			robot1_r1 = robot1_r2 = robot1_c1 = robot1_c2 = robot1_c3 = -1; // Invalidate robot variables
			break;
		}

		// Check for Robot 2
		if ((bullet_row == robot2_r1 || bullet_row == robot2_r2) &&
			(bullet_col == robot2_c1 || bullet_col == robot2_c2 || bullet_col == robot2_c3))
		{
			remove_robot(map, robot2_r1, robot2_r2, robot2_c1, robot2_c2, robot2_c3);
			robot2_r1 = robot2_r2 = robot2_c1 = robot2_c2 = robot2_c3 = -1;
			break;
		}

		// Check for Robot 3
		if ((bullet_row == robot3_r1 || bullet_row == robot3_r2) &&
			(bullet_col == robot3_c1 || bullet_col == robot3_c2 || bullet_col == robot3_c3))
		{
			remove_robot(map, robot3_r1, robot3_r2, robot3_c1, robot3_c2, robot3_c3);
			robot3_r1 = robot3_r2 = robot3_c1 = robot3_c2 = robot3_c3 = -1;
			break;
		}

		// Check for Robot 4
		if ((bullet_row == robot4_r1 || bullet_row == robot4_r2) &&
			(bullet_col == robot4_c1 || bullet_col == robot4_c2 || bullet_col == robot4_c3))
		{
			remove_robot(map, robot4_r1, robot4_r2, robot4_c1, robot4_c2, robot4_c3);
			robot4_r1 = robot4_r2 = robot4_c1 = robot4_c2 = robot4_c3 = -1;
			break;
		}

		// Check for Robot 5
		if ((bullet_row == robot5_r1 || bullet_row == robot5_r2) &&
			(bullet_col == robot5_c1 || bullet_col == robot5_c2 || bullet_col == robot5_c3))
		{
			remove_robot(map, robot5_r1, robot5_r2, robot5_c1, robot5_c2, robot5_c3);
			robot5_r1 = robot5_r2 = robot5_c1 = robot5_c2 = robot5_c3 = -1;
			break;
		}

		// Check for Robot 6
		if ((bullet_row == robot6_r1 || bullet_row == robot6_r2) &&
			(bullet_col == robot6_c1 || bullet_col == robot6_c2 || bullet_col == robot6_c3))
		{
			remove_robot(map, robot6_r1, robot6_r2, robot6_c1, robot6_c2, robot6_c3);
			robot6_r1 = robot6_r2 = robot6_c1 = robot6_c2 = robot6_c3 = -1;
			break;
		}

		// check for wals 
		if (bullet_row <= 0 || bullet_row >= Row_Size - 1 || bullet_col <= 0 || bullet_col >= Col_Size - 1 ||
			map[bullet_row][bullet_col] == '|' || map[bullet_row][bullet_col] == '-')
		{
			break;
		}

		map[bullet_row][bullet_col] = '*';
		system("cls");
		print_map(map);
		Sleep(2);
		map[bullet_row][bullet_col] = ' ';
	}
}

void fire_robot_bullet(int robotindex, char  map[][Col_Size])
{
	char robot_fire_direction;
	int current_row;
	int current_column;
	switch (robotindex)//checking the position of ethan to fire the bullet
	{
	case 1:
		current_row = robot1_r1;
		current_column = robot1_c2;
		if (prev_mid_r < current_row)
			robot_fire_direction = 'w';  // Ethan is above
		else if (prev_mid_r > current_row)
			robot_fire_direction = 's'; // Ethan is below
		else if (prev_mid2_c < current_column)
			robot_fire_direction = 'a'; // Ethan is left
		else
			robot_fire_direction = 'd'; // Ethan is right
		break;

	case 2:
		current_row = robot2_r1;
		current_column = robot2_c2;
		if (prev_mid_r < current_row)
			robot_fire_direction = 'w';
		else if (prev_mid_r > current_row)
			robot_fire_direction = 's';
		else if (prev_mid2_c < current_column)
			robot_fire_direction = 'a';
		else
			robot_fire_direction = 'd';
		break;

	case 3:
		current_row = robot3_r1;
		current_column = robot3_c2;
		if (prev_mid_r < current_row)
			robot_fire_direction = 'w';
		else if (prev_mid_r > current_row)
			robot_fire_direction = 's';
		else if (prev_mid2_c < current_column)
			robot_fire_direction = 'a';
		else
			robot_fire_direction = 'd';
		break;

	case 4:
		current_row = robot4_r1;
		current_column = robot4_c2;
		if (prev_mid_r < current_row)
			robot_fire_direction = 'w';
		else if (prev_mid_r > current_row)
			robot_fire_direction = 's';
		else if (prev_mid2_c < current_column)
			robot_fire_direction = 'a';
		else
			robot_fire_direction = 'd';
		break;

	case 5:
		current_row = robot5_r1;
		current_column = robot5_c2;
		if (prev_mid_r < current_row)
			robot_fire_direction = 'w';
		else if (prev_mid_r > current_row)
			robot_fire_direction = 's';
		else if (prev_mid2_c < current_column)
			robot_fire_direction = 'a';
		else
			robot_fire_direction = 'd';
		break;

	case 6:
		current_row = robot6_r1;
		current_column = robot6_c2;
		if (prev_mid_r < current_row)
			robot_fire_direction = 'w';
		else if (prev_mid_r > current_row)
			robot_fire_direction = 's';
		else if (prev_mid2_c < current_column)
			robot_fire_direction = 'a';
		else
			robot_fire_direction = 'd';
		break;
	}


	while (true)
	{
		switch (robot_fire_direction)
		{
		case 'w':
			current_row--;
			break;
		case 's':
			current_row++;
			break;
		case 'a':
			current_column--;
			break;
		case 'd':
			current_column++;
			break;
		}

		// Check for Ethan
		if ((current_row == prev_top_r || current_row == prev_bottom_r || current_row == prev_mid_r) &&
			(current_column == prev_bottom1_c || current_column == prev_bottom2_c || current_column == prev_mid1_c
				|| current_column == prev_mid2_c || current_column == prev_mid3_c))
		{
			ethan_lives--;
			break;
		}

		//check for boundaries and obstacles
		if (current_row <= 0 || current_row >= Row_Size - 1 || current_column <= 0 || current_column >= Col_Size - 1 ||
			map[current_row][current_column] == '|' || map[current_row][current_column] == '-')
		{
			break;
		}
		map[current_row][current_column] = '*';
		system("cls");
		print_map(map);
		Sleep(2);
		map[current_row][current_column] = ' ';
	}
}

// Function to handle high scores
void handle_high_scores(const string& currentName, int score)
{

	string names[10], temp;
	int scores[10], max;

	//read from file
	file.open("highscores.txt", ios::in);
	if (file.is_open())
	{
		int count = 0;
		while (!file.eof())
		{
			file >> names[count];
			file >> scores[count];
			count++;
			if (count == 9)
			{
				break;
			}
		}

	}
	file.close();

	//sorting the high scores
	for (int i = 0; i < 10; i++)
	{
		max = scores[i];
		for (int j = i + 1; j < 10; j++)
		{
			if (scores[j] > max)
			{
				max = scores[j];
				scores[j] = scores[i];
				scores[i] = max;

				temp = names[j];
				names[j] = names[i];
				names[i] = temp;
			}
		}
	}
	// Update the high scores
	for (int i = 0; i < 10; i++)
	{
		if (score > scores[i])
		{
			for (int j = 9; j > i; j--)
			{
				scores[j] = scores[j - 1];
				names[j] = names[j - 1];
			}
			scores[i] = score;
			names[i] = currentName;
			break;
		}
	}

	//  back to the file
	file.open("highscores.txt", ios::out);
	if (file.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			file << left << setw(20) << names[i];
			file << setw(10) << scores[i] << endl;
		}

	}
	file.close();
}

bool solo_ethan() {
	// Check if Ethan's top collides with Solo's bottom or midsection
	if ((prev_top_r == solo_r + 1 && (prev_top_c == solo_c - 1 || prev_top_c == solo_c + 1 || prev_top_c == solo_c)) || // Ethan's head with Solo's bottom
		(prev_top_r == solo_r && (prev_top_c == solo_c - 3 || prev_top_c == solo_c + 3 || prev_top_c == solo_c - 2 || prev_top_c == solo_c + 2))) { // Ethan's head with Solo's midsection
		return true;
	}

	// Check if Ethan's bottom collides with Solo's top or midsection
	else if (prev_bottom_r == solo_r - 1 && (prev_bottom1_c == solo_c - 1 || prev_bottom1_c == solo_c + 1 || prev_bottom1_c == solo_c ||
		prev_bottom2_c == solo_c - 1 || prev_bottom2_c == solo_c + 1 || prev_bottom2_c == solo_c)) { // Ethan's bottom with Solo's top or midsection
		return true;
	}

	// Check if Ethan's left collides with Solo's right side
	else if ((prev_mid_r == solo_r && prev_mid1_c == solo_c + 3) || // Left with Solo's right side
		(prev_bottom_r == solo_r && prev_bottom1_c == solo_c + 3)) { // Left with Solo's right side
		return true;
	}

	// Check if Ethan's right collides with Solo's left side
	else if ((prev_mid_r == solo_r && prev_mid3_c == solo_c - 3) || // Right arm with Solo's left side
		(prev_bottom_r == solo_r && prev_bottom2_c == solo_c - 3)) { // Right leg with Solo's left side
		return true;
	}

	// Check if Ethan's midsection collides with Solo's midsection
	else if (prev_mid_r == solo_r && (prev_mid2_c == solo_c - 1 || prev_mid2_c == solo_c + 1 || prev_mid2_c == solo_c || prev_mid2_c == solo_c - 2 || prev_mid2_c == solo_c + 2)) { // Midsection with Solo's midsection
		return true;
	}

	// Check if Ethan's head collides with Solo's left or right side (sides of head)
	else if ((prev_top_r == solo_r && (prev_top_c == solo_c - 3 || prev_top_c == solo_c + 3))) { // Ethan's head with left/right side of Solo
		return true;
	}

	// Check if Ethan's bottom collides with Solo's left or right side (sides of bottom)
	else if ((prev_bottom_r == solo_r && (prev_bottom1_c == solo_c + 3 || prev_bottom2_c == solo_c - 3))) { // Bottom with left/right side of Solo
		return true;
	}

	// Check if Ethan's legs collide with Solo's mid or bottom
	else if ((prev_bottom_r == solo_r && (prev_bottom1_c == solo_c - 1 || prev_bottom1_c == solo_c + 1 || prev_bottom1_c == solo_c)) || // Left leg with midsection or bottom
		(prev_bottom_r == solo_r && (prev_bottom2_c == solo_c - 1 || prev_bottom2_c == solo_c + 1 || prev_bottom2_c == solo_c))) { // Right leg with midsection or bottom
		return true;
	}

	return false;
}

int robot_index;
int counter = 1;
int main()
{
	system("color 1F");
	cout << "Enter your name to start the game: ";
	string playerName;
	cin >> playerName;

	cout << "Game will Start by hitting any key!" << endl;
	bool temp = false;
	char map[Row_Size][Col_Size];
	initialize_map(map);

	print_map(map);
	srand(time(0));

	update_solo();
	update_robot(1, map);
	update_robot(2, map);
	while (true)
	{
		cout << "Level: " << LEVEL << endl;
		cout << "Score: " << SCORE << endl;
		cout << "Lives remaining: " << ethan_lives << endl;
		char mov = _getch();

		if (mov == 72 || mov == 75 || mov == 77 || mov == 80)
		{
			move_ethan(map, mov);
			if (solo_ethan())
			{
				ethan_lives -= 1;
			}
			if (prev_top_r == 0 && map[prev_top_r][prev_top_c] == ' ')//if pass from door
			{
				LEVEL += 1;
				SCORE = SCORE + 5;
				ethan_lives = 3;
				if (LEVEL == 6)
				{
					system("cls");
					cout << "You Win!";
					cout << endl << "Score: " << SCORE;
					break;
				}
				temp = true;
				prev_top_r = 24, prev_top_c = 25, prev_mid_r = 25, prev_mid1_c = 24, prev_mid2_c = 25,
					prev_mid3_c = 26, prev_bottom_r = 26, prev_bottom1_c = 24, prev_bottom2_c = 26;
				initialize_map(map);
			}

			if (temp)
			{
				switch (LEVEL)
				{
				case 2:
					update_solo();

					update_robot(1, map);
					update_robot(2, map);
					update_robot(3, map);
					break;

				case 3:
					update_solo();

					update_robot(1, map);
					update_robot(2, map);
					update_robot(3, map);
					update_robot(4, map);
					break;

				case 4:
					update_solo();

					update_robot(1, map);
					update_robot(2, map);
					update_robot(3, map);
					update_robot(4, map);
					update_robot(5, map);
					break;

				case 5:
					update_solo();

					update_robot(1, map);
					update_robot(2, map);
					update_robot(3, map);
					update_robot(4, map);
					update_robot(5, map);
					update_robot(6, map);
					break;
				}
				temp = false;
			}
		}
		else if (mov == 'w' || mov == 'a' || mov == 's' || mov == 'd' || mov == 'W' || mov == 'A' || mov == 'S' || mov == 'D')
		{
			fire_bullet(map, mov);//ethan firing

		}

		// robot firing after every 10 movements
		if (counter % 10 == 0)
		{
			robot_index = rand() % (LEVEL + 1) + 1; // seleccting random roboots
			fire_robot_bullet(robot_index, map);
		}
		if (counter % 20 == 0)//score increase after 10 seconds
		{
			SCORE++;
		}

		if (ethan_lives == 0)
		{
			system("cls");
			cout << "Game Over!" << endl << "You Lost!" << endl;
			cout << "Score:   h" << SCORE;
			break;
		}
		counter++;
		system("cls");
		print_map(map);
	}
	handle_high_scores(playerName, SCORE);
	return 0;
}