#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>
#define NUMBER 13
#define SIZE 1000
#define length 100
//玩家模型 
static struct Player {
	int points;
	int refuse;
	int score;
}player5;
static struct Bot
{
	int points;
	int refuse;
}bot;

static void reset_game5() {
	player5.points = 0;
	player5.refuse = 0;
	bot.points = 0;
	bot.refuse = 0;
}
static int game5() {
	//初始化游戏--------------------------------------------
	reset_game5();
	int point_tmp = 0;
	int point_sum = 0;
	int choose = 1;
	//主体循环--------------------------------------------
	while (!player5.refuse) {
		point_tmp = (rand() % 13) + 1;
		player5.points += point_tmp;
		printf("\n");
		printf("你拿到牌的点数是:%d\n", point_tmp);
		printf("你的总点数是:%d\n", player5.points);
		if (player5.points > 21) {
			printf("点数超过了21点,你输了\n");
			player5.score -= 200;
			return 0;
		}
		else {
			printf("你还要继续要牌吗?(1/是  0/否):"); scanf("%d", &choose);
			if (!choose) {
				break;
			}
		}
	}
	bot.points = rand() % 21 + 1;
	if (bot.points <= 10) {
		bot.points += 10;
	}

	//判断输赢-------------------------------------------
	if (player5.points > bot.points) {
		printf("你的总点数是:%d\n", player5.points);
		printf("电脑的总点数:%d\n", bot.points);
		printf("你赢了\n");
		player5.score += 100;
	}
	if (player5.points == bot.points) {
		printf("你的总点数是:%d\n", player5.points);
		printf("电脑的总点数:%d\n", bot.points);
		printf("平局\n");
	}
	if (player5.points < bot.points) {
		printf("你的总点数是:%d\n", player5.points);
		printf("电脑的总点数:%d\n", bot.points);
		printf("你输了\n");
	}
	return 0;
}

static int game_5_heyjack()
{
	int score, choose = 1;
	player5.score = 100;
	printf("欢迎游玩21点\n");
	printf("你将有100基础得分\n");
	printf("赢得游戏+100,没有爆掉牌而输掉游戏-100,爆牌而输将-200\n");
	printf("你可以持续要牌直到你不想要或者爆掉为止\n");
	printf("超过21点将直接爆牌\n");
label5:
	game5();
	printf("\n继续游玩21点？(1/是 0/否):");
	scanf("%d", &choose);
	if (choose) {
		goto label5;
	}
	printf("你的分数是:%d", player5.score);
	return player5.score;
}