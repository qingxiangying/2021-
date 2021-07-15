#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#include <string.h>
#pragma comment(lib,"libmysql.lib")
#include "game1.cpp"
#include "game2.cpp"
#include "game3.cpp"
#include "game4.cpp"
#include "game5.cpp"
#include "game6.cpp"

//定义全局变量，用户的sid
int sid = 0;

typedef struct g {
	int gid;
	int score;
}game;

void ScorePrint(MYSQL* mysqlPrint) {

	MYSQL_RES* result;/*指向查询结果的指针*/
	int numFields = 0;
	int numRows = 0;
	MYSQL_FIELD* field;/*字段结构指针*/
	MYSQL_ROW row; /*按行返回的查询信息*/
	int i = 0;
	result = mysql_store_result(mysqlPrint);//将查询的全部结果读取到客户端
	numFields = mysql_num_fields(result);//统计结果集中的字段数
	numRows = mysql_num_rows(result);//统计结果集的行数
	while (field = mysql_fetch_field(result))//返回结果集中的列信息(字段)
		printf("%s\t", field->name);
	printf("\n");
	if (result)
	{
		while (row = mysql_fetch_row(result))//返回结果集中行的记录
		{
			for (i = 0; i < numFields; i++)
			{
				printf("%s\t", row[i]);
			}
			printf("\n");
		}
	}
	mysql_free_result(result);//释放result空间，避免内存泄漏
}

//该函数执行一个select型的sql语句，并打印出值，若失败则反回0
void SelectMYSQL(MYSQL* mysql, const char* query) {
	int res;

	res = mysql_real_query(mysql, query, strlen(query));
	//如果是0则执行成功
	if (res) {
		printf("failed");
	}
	else {
		ScorePrint(mysql);
	}
}

void Show_ranking_list(MYSQL* mysql) {
	int gid;
	char query[200] = { 0 };
	printf("请选择你的游戏\n");
	printf("1.....飞机大战\n");
	printf("2.....扫    雷\n");
	printf("3.....2 0 4  8\n");
	printf("4.....贪 吃 蛇\n");
	printf("5.....2  1  点\n");
	printf("6.....球球大战\n");
	scanf("%d", &gid);

	sprintf(query, "SELECT s.sname 用户名 ,p.score 分数 FROM student s,play p WHERE s.sid = p.sid AND p.gid = %d ORDER BY p.score DESC LIMIT 5 ", gid);
	//printf("%s", query);
	SelectMYSQL(mysql, query);

}

game* (Game(MYSQL* mysql))
{
	game play = { 0 };
	printf("请选择你的操作\n");
	printf("1.....飞机大战\n");
	printf("2.....扫    雷\n");
	printf("3.....2 0 4  8\n");
	printf("4.....贪 吃 蛇\n");
	printf("5.....2  1  点\n");
	printf("6.....球球大战\n");
	printf("7.....排 行 榜\n");
	printf("8.....退    出\n");
	scanf("%d", &play.gid);
	switch (play.gid) {
	case 1: play.score = game_1_plane(); return &play; break;
	case 2: play.score = game_2_mineClearance(); return &play; break;
	case 3: play.score = game_3_2048(); return &play;break;
	case 4: play.score = game_4_snack(); return &play; break;
	case 5: play.score = game_5_heyjack(); return &play; break;
	case 6: play.score = game_6_qiuqiu();return &play; break;
	case 7:Show_ranking_list(mysql); return 0; break;
	case 8: printf("已经退出游戏系统！"); return &play;
	}

}

void InsertScore(MYSQL* mysql, int sid, int gid, int score)
{
	int t;
	char query[120];

	/* 拼接sql命令 */
	sprintf(query, "INSERT INTO play VALUES (null,%d,%d,%d)", sid, gid, score);
	//printf("%s\n", query);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
		//printf("Failed to query: %s\n", mysql_error(mysql));
	}
	else {
		//printf("\nInsert sucessfully!\n");
	}

}

const char* (FindMYSQL(MYSQL* mysql, const char* find_table, const char* find_name, const char* field_name, const char* id))
{
	MYSQL_RES* result;
	int numFields = 0;
	int numRows = 0;
	MYSQL_FIELD* field;/*字段结构指针*/
	MYSQL_ROW row; /*按行返回的查询信息*/
	const char* tresult;
	int t;

	char query[120];

	sprintf(query, "SELECT %s FROM %s WHERE %s =\"%s\"", find_name, find_table, field_name, id);
	//printf("%s\n", query);

	int res = mysql_query(mysql, query);
	if (res) {
		printf("failed");
		return "";
	}
	else {
		result = mysql_store_result(mysql);//将查询的全部结果读取到客户端
		numFields = mysql_num_fields(result);//统计结果集中的字段数
		numRows = mysql_num_rows(result);//统计结果集的行数
		while (field = mysql_fetch_field(result))//返回结果集中的列信息(字段)
			//printf("%s\t", field->name);
			printf("\n");
		if (result)
		{
			while (row = mysql_fetch_row(result))//返回结果集中行的记录
			{
				for (int i = 0; i < numFields; i++)
				{
					//printf("%s\t", row[i]);
					mysql_free_result(result);//释放result空间，避免内存泄漏
					return row[i];
				}
				printf("\n");
			}
		}
		else {
			return NULL;
		}
	}

}

MYSQL* (Connect(MYSQL connect)) {
	mysql_init(&connect);

	//实际连接数据库
	if (mysql_real_connect(&connect, "localhost", "root", "123456", "G", 3306, 0, 0)) {
		//printf("连接成功\n");
		//设置编码格式
		mysql_query(&connect, "set names gbk;");
		return &connect;
	}
	else {
		//printf("连接失败");
		exit(-1);
	}
}

int LoginIn(MYSQL* mysql)
{

	const char* acount;
	char scanf_acount[20] = { 0 };
	char scanf_password[20] = { 0 };
	const char* password;
	int choice = -1;

	printf("请输入账号：");
	scanf("%s", scanf_acount);
	printf("请输入密码：");
	scanf("%s", scanf_password);
	acount = FindMYSQL(mysql, "student", "acount", "acount", scanf_acount);
	if (acount) {
		password = FindMYSQL(mysql, "student", "password", "acount", scanf_acount);
		if (strcmp(password, scanf_password) == 0) {
			printf("登录成功！\n欢迎用户登录！\n");
			sid = atoi(FindMYSQL(mysql, "student", "sid", "acount", scanf_acount));
			//printf("\n%d!!!!!!!!\n",sid);
			return choice;

		}
		else {
			printf("密码错误！\n是否注册？（1.yes，0.no）:");
			scanf("%d", &choice);
			return choice;

		}
	}
	else {
		printf("用户不存在！\n是否注册？（1.yes，0.no）:");
		scanf("%d", &choice);
		return choice;
	}
}

void LoginUp(MYSQL* mysql)
{
	int t;
	char query[120] = { 0 };
	char sname[20] = { 0 };
	char acount[20] = { 0 };
	char password[20] = { 0 };

	printf("请输入用户名：");
	scanf("%s", sname);
	printf("请输入账号：");
	scanf("%s", acount);
	printf("请输入密码：");
	scanf("%s", password);

	char i = '"';

	/* 拼接sql命令 */
	sprintf(query, "INSERT INTO student values (null, %c%s%c, %c%s%c, %c%s%c)", i, sname, i, i, acount, i, i, password, i);
	//printf("%s\n", query);

	t = mysql_real_query(mysql, query, strlen(query));
	if (t) {
		//printf("Failed to query: %s\n", mysql_error(mysql));
		printf("注册失败！\n");
	}
	else {
		//printf("\nInsert sucessfully!\n");
		printf("注册成功!\n");
	}

}

int main() {
	MYSQL connect = { 0 };
	MYSQL* mysql = NULL;
	game* play = NULL;
	int choice;

	mysql = Connect(connect);
	printf("欢迎！\n请输入您的选择(1.登录，2.注册，0.退出本系统）：");
	scanf("%d", &choice);
	while (choice) {
		if (choice == 1) {
		loginin:
			int e = LoginIn(mysql);
			if (e == -1) {
				printf("欢迎进入游戏系统！");
			}
			else if (e == 1) {
				goto loginup;
			}
			else if (e == 0) {
				goto loginin;
			}

		playagain:
			play = Game(mysql);
			if (play != NULL)
				InsertScore(mysql, sid, play->gid, play->score);
			int ch = 0;
			printf("是否重新进入游戏系统？(1.yes，0.no)");
			scanf("%d", &ch);
			if (ch == 1) goto playagain; else {
				printf("请输入您的选择(1.登录，2.注册，0.退出本系统）：");
				scanf("%d", &choice);
			}
		}
		else if (choice == 2) {
		loginup:
			LoginUp(mysql);
			printf("请输入您的选择(1.登录，2.注册，0.退出本系统）：");
			scanf("%d", &choice);
		}
		else {
			;
			printf("无法识别的选项（？\n请输入您的选择(1.登录，2.注册，0.退出本系统）：");
			scanf("%d", &choice);
		}
	}

	mysql_close(&connect);

	return 0;

}