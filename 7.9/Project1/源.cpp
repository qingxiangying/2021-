#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")

void select_book(MYSQL *connect_p) {
	char book_name[100],s[200];
	int res=0;//执行SQL语句后的返回值
	MYSQL_RES* res_ptr; /*指向查询结果的指针*/
	MYSQL_FIELD* field; /*字段结构指针*/
	MYSQL_ROW result_row; /*按行返回的查询信息*/
	int row, column; /*查询返回的行数和列数*/
	int i, j;
	char* str_sql = s;
	char sql[100] = { '\0' };
	printf("请输入书名信息:");
	scanf("%s", book_name);
	strcpy(str_sql, "select * from book where book_name='");
	str_sql = strcat(str_sql, book_name);
	str_sql = strcat(str_sql, "';\0");
	printf("%s",str_sql);
	strcpy(sql, str_sql);
	res = mysql_query(connect_p,sql);
	printf("res=%d\n", res);
	if (!res) {
		printf("\n正在查询\n");
		res_ptr = mysql_store_result(connect_p);
		if (res_ptr) {
			column = mysql_num_fields(res_ptr);
			row = mysql_num_rows(res_ptr) + 1;
			//打印列名
			for (i = 0;(field = mysql_fetch_fields(res_ptr) + i) && i < column;i++) {
				printf("\t%10s\t", field->name);
			}
			//打印具体内容
			printf("\n");
			for (i = 1; i < row; i++) {
				result_row = mysql_fetch_row(res_ptr);
				for (j = 0; j < column; j++)
					printf("\t%10s\t", result_row[j]);
				printf("\n");
			}
		}
	}
	else
	{
		printf("查询失败");
	}
}
void borrowbook(MYSQL *connect_p,char user_name[100]) {
	char book_name[100], s[200];
	int res = 0;//执行SQL语句后的返回值
	MYSQL_RES* res_ptr; /*指向查询结果的指针*/
	MYSQL_FIELD* field; /*字段结构指针*/
	MYSQL_ROW result_row; /*按行返回的查询信息*/
	int row, column; /*查询返回的行数和列数*/
	int i, j;
	char* str_sql = s;
	char sql[100] = { '\0' };
	char up1[100] = { '\0' };char* update1 = up1;
	char up2[100] = { '\0' };char* update2 = up2;
	printf("请输入书名信息:");
	scanf("%s", book_name);
	strcpy(str_sql, "select book_state,book_id from book where book_name='");
	str_sql = strcat(str_sql, book_name);
	str_sql = strcat(str_sql, "';\0");
	printf("%s", str_sql);
	strcpy(sql, str_sql);
	res = mysql_query(connect_p, sql);
	printf("res=%d\n", res);
	if (!res) {
		printf("正在查询");
		res_ptr = mysql_store_result(connect_p);
		if (res_ptr) {
			result_row = mysql_fetch_row(res_ptr);
			printf("%s", result_row[0]);
			int tmp = atoi(result_row[0]);
			char *book_id = result_row[1];
			mysql_free_result(res_ptr);
			if (tmp == 1) {
				printf("该图书已被借出\n借阅失败");
			}
			else{
				int flag = 1;
				strcpy(update1,"update book set book_state=0 where book_name='");
				update1 = strcat(update1, book_name);
				strcpy(update1, "';\0");
				printf("%s", update1);
				res = mysql_query(connect_p, update1);
				if (res != 0) {
					flag = 0*flag;
				}
				res_ptr = mysql_store_result(connect_p);
				mysql_free_result(res_ptr);
				strcpy(update2, "insert into borrow values (null,'");
				strcpy(update2, user_name);
				strcpy(update2, "',");
				strcpy(update2, book_id);
				strcpy(update2, "',0);\0");
//				printf("%s", update2);
				res = mysql_query(connect_p, update2);
				if (res != 0) {
					flag = 0*flag;
				}
				res_ptr = mysql_store_result(connect_p);
				if (flag) {
					printf("借阅成功");
				}
			}
		}
	}
	else
	{
		printf("借阅失败");
	}
}
int backbook(MYSQL* connect_p,char user_name[100]) {
	char book_name[100], s[200];
	int res = 0;//执行SQL语句后的返回值
	MYSQL_RES* res_ptr; /*指向查询结果的指针*/
	MYSQL_FIELD* field; /*字段结构指针*/
	MYSQL_ROW result_row; /*按行返回的查询信息*/
	int row, column; /*查询返回的行数和列数*/
	int i, j,isback,flag=1;
	char* str_sql = s;
	char sql[100] = { '\0' };
	char up1[100] = { '\0' };char* update1 = up1;
	char up2[100] = { '\0' };char* update2 = up2;
	printf("请输入要归还的书名信息:");
	scanf("%s", book_name);
	sprintf(str_sql, "selece top 1 isback from borrow where u_name='%s' and book_id=(select from book where book_name='%s') order by isback;", user_name,book_name);
	printf("%s", str_sql);
	res = mysql_query(connect_p, str_sql);
	if (!res) {
		res_ptr = mysql_store_result(connect_p);
		if (res_ptr) {
			result_row = mysql_fetch_row(res_ptr);
			isback =atoi(result_row[0]);
			if (isback == 1) {
				printf("你已经归还，无需操作");
				return 0;
			}
			mysql_free_result(res_ptr);
			sprintf(update1, "update borrow set isback=1 where u_name='%s' and book_id=(select from book where book_name='%s';)", user_name, book_name);
			res = mysql_query(connect_p, update1);
			if (res != 0) {
				flag = flag * 0;
			}
			res_ptr = mysql_store_result(connect_p);
			mysql_free_result(res_ptr);
			sprintf(update2, "update book set book_state=0 where boo_name='%s';", book_name);
			res = mysql_query(connect_p, update2);
			if (res != 0) {
				flag = flag * 0;
			}
			res_ptr = mysql_store_result(connect_p);
			mysql_free_result(res_ptr);
			if (flag == 1) {
				printf("归还成功");
				return 1;
			}
			printf("归还失败");
			return 0;
		}
		else {
			return 0;
		}
	}
	return 0;
}

void opadmin(char u_name[100],MYSQL *connect_p) {
	printf("\t1......添加图书\n");
	printf("\t2......删除图书\n");
	printf("\t3......修改图书信息\n");
	printf("\t4......退出系统");
}

int opuser(char u_name[100],MYSQL *connect_p) {
label:
	printf("\n\t----------------------------------------------\t\n");
	printf("\t1......借阅图书.....\n");
	printf("\t2......归还图书.....\n");
	printf("\t3......查询图书.....\n");
	printf("\t4......退出系统.....\n");
	int tmp = 0;
	scanf("%d", &tmp);
	switch(tmp) {
		case 4: printf("已退出系统\n");return 0;
		case 3: printf("请稍等\n"); select_book(connect_p);break;
		case 1: printf("请稍等\n");borrowbook(connect_p,u_name);break;
		case 2: printf("请稍等\n");backbook(connect_p, u_name);break;
	}
	goto label;

}
int main() {
	MYSQL connect;
	char u_name[100], u_pwd[100],s[100];
	char *str_sql=s;
	int res;//执行SQL语句后的返回值
	char sql[200], ch;
	MYSQL_RES* res_ptr; /*指向查询结果的指针*/
	MYSQL_FIELD* field; /*字段结构指针*/
	MYSQL_ROW result_row; /*按行返回的查询信息*/
	int row, column; /*查询返回的行数和列数*/
	int i, j, admin = 0;
	//初始化连接数据库
	mysql_init(&connect);

	//实际连接数据库s
	if (mysql_real_connect(&connect, "localhost", "root", "123456", "test", 0, 0, 0)) {
		printf("连接成功\n欢迎使用图书管理系统\n");
		//设置编码格式
		mysql_query(&connect, "set names gbk;");
//----------------------------------------------分割线-----------------------------
	lable:	
		printf("请输入你的账号:");scanf("%s", u_name);
		printf("请输入你的密码:");scanf("%s", u_pwd);
		strcpy(str_sql, "select isadmin from user where u_name='");
		str_sql = strcat(str_sql,u_name);
		str_sql = strcat(str_sql, "' and u_pwd='");
		str_sql = strcat(str_sql, u_pwd);
		str_sql = strcat(str_sql, "';\0");
		printf("%s\n", str_sql);

//		strcpy(sql, str_sql);
		res = mysql_query(&connect, str_sql);
		if (!res) {
			res_ptr = mysql_store_result(&connect);
			if (res_ptr) {
				result_row = mysql_fetch_row(res_ptr);
				if (result_row == NULL) {
					printf("密码错误或者用户不存在\n");
					goto lable;
				}
				int tmp = atoi(result_row[0]);
				//打印具体内容
				printf("\n");
				if ( tmp == 1) {
					printf("欢迎管理员%s登录", u_name);
					admin = 1;
				}
				else if (tmp == 0) {
					printf("欢迎用户%s登录", u_name);
				}
			}
			mysql_free_result(res_ptr);
		}
		printf("\n\n");
//---------------------------------------------------------分割线----------------------------------------------
		strcpy(sql,"select book_id '图书编号',book_name '图书名',book_auth '作者',book_state '图书是否已经借出' from book");
		res = mysql_query(&connect, sql);
		if (!res) {
			res_ptr = mysql_store_result(&connect);
			if (res_ptr) {
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr)+1;
				//打印列名
				for (i = 0;(field = mysql_fetch_fields(res_ptr)+i) && i<column;i++) {
					printf("\t%10s\t", field->name);
				}
				//打印具体内容
				printf("\n");
				for (i = 1; i < row; i++) {
					result_row = mysql_fetch_row(res_ptr);
					for (j = 0; j < column; j++)
						printf("\t%10s\t", result_row[j]);
					printf("\n");
				}
			}
			mysql_free_result(res_ptr);
		}
	}
	else {
		printf("图书管理系统连接失败\n已经退出系统");
		exit(-1);
		mysql_close(&connect);
	}
//----------------------------------------------------------------------------------------------------
	if (admin) {
		opadmin(u_name,&connect);
	}
	else
	{
		opuser(u_name,&connect);
	}


	mysql_close(&connect);

	return 0;
}