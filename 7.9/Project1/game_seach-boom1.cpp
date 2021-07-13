#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<time.h>
#define ROW 12
#define COL 12
#define MINE_NUM 15
#define TOTAL 100
#pragma warning(disable:4996)
int count = TOTAL;
void inter() {
	printf("=======================\n");
	printf("=======游戏菜单========\n");
	printf("======1.开始游戏=======\n");
	printf("========2.退出=========\n");
	printf("=======================\n");
	printf("请输入您的选择： \n");
}
int GetRandIndex(int start, int end) {
	return rand() % (end - start + 1) + start;
}
void layout(char mine[][COL], int row, int col) {
	srand((unsigned long)time(NULL));
	int count = 0;
	while (count < MINE_NUM) {
		int x = GetRandIndex(1, 10);
		int y = GetRandIndex(1, 10);
		if (mine[x][y] == '0') {
			mine[x][y] = '1';
			count++;
		}
	}
}

void Board(char board[][COL], int row, int col) {
	printf(" ");
	int i = 1;
	for (; i <= 10; i++)
	{
		printf(" %d ", i);
	}
	printf("\n----");
	for (i = 1; i <= 29; i++)
	{
		printf("-");
	}
	printf("\n");
	for (i = 1; i <= 10; i++)
	{
		printf("%2d|", i);
		int j = 1;
		for (; j <= 10; j++) {
			printf(" %c|", board[i][j]);
		}
		printf("\n");
		int k = 1;
		for (k = 1; k <= 11; k++)
		{
			printf("---");
		}
		printf("\n");
	}
}

char GetMines(char mine[][COL], int row, int col) {
	return mine[row - 1][col - 1] + mine[row - 1][col] + mine[row - 1][col + 1]\
		+ mine[row][col - 1] + mine[row][col + 1]\
		+ mine[row + 1][col - 1] + mine[row + 1][col] + mine[row + 1][col + 1] - 7 * '0';
}
void expand(char mine[ROW][COL], char board[ROW][COL], int x, int y) {
	if ((x >= 1) && (y >= 1) && (x <= ROW) && (y <= COL))
	{
		if (GetMines(mine, x, y) == '0')
		{
			if (x > 1 && x < 10 && y>1 && y < 10)
			{
				count = count - 8;
			}
			else if ((x == 1 && y == 1) || (x == 10 && y == 10) || (x == 1 && y == 10) || (x == 10 && y == 1)) {
				count -= 3;
			}
			else {
				count -= 5;
			}
			board[x - 1][y - 1] = GetMines(mine, x - 1, y - 1);
			board[x - 1][y] = GetMines(mine, x - 1, y);
			board[x - 1][y + 1] = GetMines(mine, x - 1, y + 1);
			board[x][y - 1] = GetMines(mine, x, y - 1);
			board[x][y + 1] = GetMines(mine, x, y + 1);
			board[x + 1][y - 1] = GetMines(mine, x + 1, y - 1);
			board[x + 1][y] = GetMines(mine, x + 1, y);
			board[x + 1][y + 1] = GetMines(mine, x + 1, y + 1);
		}
	}
}
void Game() {
	char mine[ROW][COL];
	char board[ROW][COL];
	memset(mine, '0', sizeof(mine));
	memset(board, '*', sizeof(board));
	layout(mine, ROW, COL);
	Board(mine, ROW, COL);
	int x = 0;
	int y = 0;
	while (1) {
		int i = 0;
		Board(board, ROW, COL);
		printf("请选择您要排除的位置： ");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= ROW - 2 && y >= 1 && y <= COL - 2) {
			if (mine[x][y] == '0') {
				char num = GetMines(mine, x, y);
				board[x][y] = num;
				expand(mine, board, x, y);
				Board(board, ROW, COL);
				count--;
				if (count == MINE_NUM)
				{
					Board(board, ROW, COL);
					printf("你赢了！\n");
					break;
				}
			}
			else {
				printf("您输了！\n");
				Board(mine, ROW, COL);
				break;
			}
			printf("还有%d个位置 \n", count);
		}
		else {
			printf("你输入的坐标有误，请重新输入！\n");
		}
	}
}
/*int main() {
	int quit = 0;
	int select = 0;
	while (!quit) {
		inter();
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			Game();
			Sleep(5000);
			system("cls");
			break;
		case 2:
			printf("再见！\n");
			quit = 1;
			break;
		default:
			printf("您的输入不正确，请重新输入！\n");
			break;
		}
	}
	system("pause");
	return 0;
}*/