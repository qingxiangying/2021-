// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")


int main() {
	MYSQL connect;
	int res;//执行SQL语句后的返回值
	char sql[100];
	MYSQL_RES* res_ptr; /*指向查询结果的指针*/
	MYSQL_FIELD* field; /*字段结构指针*/
	MYSQL_ROW result_row; /*按行返回的查询信息*/
	int row, column; /*查询返回的行数和列数*/
	int i, j; /*只是控制循环的两个变量*/
	//初始化连接数据库
	mysql_init(&connect);
	char str_sql[100];
//	strcpy_s(sql, str_sql);


	//实际连接数据库
	if (mysql_real_connect(&connect, "localhost", "root", "123456", "test", 0, 0, 0)) {
		printf("连接成功\n");
		//设置编码格式
		mysql_query(&connect, "set names gbk;");
		strcpy_s(sql, "select * from student");
		res = mysql_query(&connect, sql);
		//如果是0则执行成功
		if (res) {
			printf("执行失败！\n");
			mysql_close(&connect);
		}
		else {
			res_ptr = mysql_store_result(&connect);
			/*如果结果不为空，就把结果printf*/
			if (res_ptr) {
				/*取得結果的行数和*/
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr) + 1;
				/*输出結果的字段名*/
				for (i = 0; field = mysql_fetch_field(res_ptr); i++)
					printf("%s\t", field->name);
				printf("\n");


				/*按行输出结果*/
				for (i = 1; i < row; i++) {
					result_row = mysql_fetch_row(res_ptr);
					for (j = 0; j < column; j++)
						printf("%s\t", result_row[j]);
					printf("\n");
				}
			}
			/*不要忘了关闭连接*/
			mysql_close(&connect);
		}
	}
	else {
		printf("连接失败");
	}

	mysql_close(&connect);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
