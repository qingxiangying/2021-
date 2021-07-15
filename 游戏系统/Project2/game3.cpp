#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>

static int null_count();//统计还有几个空格
static void start_game();//开始游戏
static void reset_game();//重置游戏，不清空记录
static void move_left();//向左移动
static void move_right();//向右移动
static void move_up();//向上移动
static void move_down();//向下移动
static void refresh_show();//刷新显示屏
static void add_rand_num();//添加随机数
static void check_if_over();//检查游戏是否结束

static int board[4][4];
static int score = 0;
static int best = 0;
static int if_need_add_num;
static int if_game_over;
static int i;
static int j;


static int game_3_2048() {
	start_game();
	printf("将取你最好的成绩存入排行榜\n");
	return best;
}

static void setColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);
}

static void start_game() {
	reset_game();
	char fr;
	while (1) {
		fr = _getch();//从键盘读数
		if (if_game_over) {
			if (fr == 'y' || fr == 'Y') {
				reset_game();
				continue;
			}
			else if (fr == 'n' || fr == 'N') {
				return;
			}
			else continue;
		}
		if_need_add_num = 0;
		switch (fr) {
		case 'a':
		case 'A':
			move_left();
			break;
		case 'd':
		case 'D':
			move_right();
			break;
		case 'w':
		case 'W':
			move_up();
			break;
		case 's':
		case 'S':
			move_down();
			break;
		}
		if (score > best) {
			best = score;
		}
		if (if_need_add_num) {
			add_rand_num();
			refresh_show();
		}
	}
}

static int null_count() {
	int n = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				n++;
			}
		}
	}
	return n;
}

static void reset_game() {
	score = 0;
	if_need_add_num = 1;
	if_game_over = 0;
	srand(time(0));
	int n = rand() % 16;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (n == 0) {
				int k = rand() % 3;
				if (k == 0 || k == 1) {
					board[i][j] = 2;
				}
				else {
					board[i][j] = 4;
				}
				n--;
			}
			else {
				board[i][j] = 0;
				n--;
			}

		}
	}
	add_rand_num();
	system("cls");
	refresh_show();
}

static void move_left() {
	int k;
	for (i = 0; i < 4; i++) {
		for (j = 1, k = 0; j < 4; j++) {
			if (board[i][j] > 0) {
				if (board[i][k] == board[i][j]) {
					board[i][k] *= 2;
					k++;
					score = score + 2 * board[i][j];
					board[i][j] = 0;
					if_need_add_num = 1;
				}
				else if (board[i][k] == 0) {
					board[i][k] = board[i][j];
					board[i][j] = 0;
					if_need_add_num = 1;
				}
				else {
					board[i][k + 1] = board[i][j];
					if ((k + 1) != j) {
						board[i][j] = 0;
						if_need_add_num = 1;
					}
					k++;
				}
			}
		}
	}
}

static void move_right() {
	int k;
	for (i = 0; i < 4; i++) {
		for (j = 2, k = 3; j >= 0; j--) {
			if (board[i][j] > 0) {
				if (board[i][k] == board[i][j]) {
					board[i][k] *= 2;
					k--;
					score = score + 2 * board[i][j];
					board[i][j] = 0;
					if_need_add_num = 1;
				}
				else if (board[i][k] == 0) {
					board[i][k] = board[i][j];
					board[i][j] = 0;
					if_need_add_num = 1;
				}
				else {
					board[i][k - 1] = board[i][j];
					if ((k - 1) != j) {
						board[i][j] = 0;
						if_need_add_num = 1;
					}
					k--;
				}
			}
		}
	}
}

static void move_up() {
	int k;
	for (i = 0; i < 4; i++) {
		for (j = 1, k = 0; j < 4; j++) {
			if (board[j][i] > 0) {
				if (board[k][i] == board[j][i]) {
					board[k][i] *= 2;
					k++;
					score = score + 2 * board[j][i];
					board[j][i] = 0;
					if_need_add_num = 1;
				}
				else if (board[k][i] == 0) {
					board[k][i] = board[j][i];
					board[j][i] = 0;
					if_need_add_num = 1;
				}
				else {
					board[k + 1][i] = board[j][i];
					if ((k + 1) != j) {
						board[j][i] = 0;
						if_need_add_num = 1;
					}
					k++;
				}
			}
		}
	}
}

static void move_down() {
	int k;
	for (i = 0; i < 4; i++) {
		for (j = 2, k = 3; j >= 0; j--) {
			if (board[j][i] > 0) {
				if (board[k][i] == board[j][i]) {
					board[k][i] *= 2;
					k--;
					score = score + 2 * board[j][i];
					board[j][i] = 0;
					if_need_add_num = 1;
				}
				else if (board[k][i] == 0) {
					board[k][i] = board[j][i];
					board[j][i] = 0;
					if_need_add_num = 1;
				}
				else {
					board[k - 1][i] = board[j][i];
					if ((k - 1) != j) {
						board[j][i] = 0;
						if_need_add_num = 1;
					}
					k--;
				}
			}
		}
	}
}

static void refresh_show() {
	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("GAME: 2048     SCORE: %6d    BEST: %6d\n", score, best);
	printf("*************************************************************\n\n");
	printf("       ┌───┬───┬───┬───┐\n");
	for (int i = 0; i < 4; i++)
	{
		printf("       │");
		for (int j = 0; j < 4; j++) {
			if (board[i][j] != 0)
			{
				if (board[i][j] < 10)
				{
					if (board[i][j] == 2)
					{
						setColor(14, 0);
					}
					else if (board[i][j] == 4)
					{
						setColor(6, 0);
					}
					else if (board[i][j] == 8)
					{
						setColor(12, 0);
					}
					printf("  %d", board[i][j]);
					setColor(7, 0);
					printf("   │");
				}
				else if (board[i][j] < 100)
				{
					if (board[i][j] == 16)
					{
						setColor(4, 0);
					}
					else if (board[i][j] == 32)
					{
						setColor(10, 0);
					}
					else if (board[i][j] == 64)
					{
						setColor(2, 0);
					}
					printf("  %d", board[i][j]);
					setColor(7, 0);
					printf("  │");
				}
				else if (board[i][j] < 1000)
				{
					if (board[i][j] == 128)
					{
						setColor(9, 0);
					}
					else if (board[i][j] == 256)
					{
						setColor(1, 0);
					}
					else if (board[i][j] == 512)
					{
						setColor(13, 0);
					}
					printf("  %d", board[i][j]);
					setColor(7, 0);
					printf(" │");
				}
				else if (board[i][j] < 10000)
				{
					if (board[i][j] == 1024)
					{
						setColor(5, 0);
					}
					else
					{
						setColor(15, 0);
					}
					printf(" %4d", board[i][j]);
					setColor(7, 0);
					printf(" │");
				}
				else
				{
					int n = board[i][j];
					for (int k = 1; k < 30; k++)
					{
						n /= 2;
						if (n == 1)
						{
							setColor(7, 0);
							printf("2^%2d |", k);
							break;
						}
					}
				}
			}
			else
			{
				setColor(0, 0);
				printf("     ");
				setColor(7, 0);
				printf(" │");
			}
		}
		setColor(7, 0);
		if (i <= 2)
		{
			printf("\n       ├───┼───┼───┼───┤\n");
		}
		else printf("\n       └───┴───┴───┴───┘\n\n");
	}
	printf("*************************************************************\n\n");
	printf("w↑ ↓s  a←  →d    输入方向键后请按回车读入:  ");
	if (null_count() == 0) {
		check_if_over();
		if (if_game_over) {
			printf("\nGAME OVER,TRY AGAIN?[Y/N]:");
		}
	}
}

static void add_rand_num() {
	int k;
	srand(time(0));
	int n = rand() % null_count();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board[i][j] == 0) {
				if (n != 0) {
					n--;
				}
				else {
					int k = rand() % 3;
					if (k == 0 || k == 1) {
						board[i][j] = 2;
						return;
					}
					else {
						board[i][j] = 4;
						return;
					}
				}
			}
		}
	}
}

static void check_if_over() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == board[i][j + 1] || board[j][i] == board[j + 1][i]) {
				if_game_over = 0;
				return;
			}
		}
	}
	if_game_over = 1;
}