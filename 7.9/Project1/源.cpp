#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")

void select_book(MYSQL *connect_p) {
	char book_name[100],s[200];
	int res=0;//ִ��SQL����ķ���ֵ
	MYSQL_RES* res_ptr; /*ָ���ѯ�����ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	int row, column; /*��ѯ���ص�����������*/
	int i, j;
	char* str_sql = s;
	char sql[100] = { '\0' };
	printf("������������Ϣ:");
	scanf("%s", book_name);
	strcpy(str_sql, "select * from book where book_name='");
	str_sql = strcat(str_sql, book_name);
	str_sql = strcat(str_sql, "';\0");
	printf("%s",str_sql);
	strcpy(sql, str_sql);
	res = mysql_query(connect_p,sql);
	printf("res=%d\n", res);
	if (!res) {
		printf("\n���ڲ�ѯ\n");
		res_ptr = mysql_store_result(connect_p);
		if (res_ptr) {
			column = mysql_num_fields(res_ptr);
			row = mysql_num_rows(res_ptr) + 1;
			//��ӡ����
			for (i = 0;(field = mysql_fetch_fields(res_ptr) + i) && i < column;i++) {
				printf("\t%10s\t", field->name);
			}
			//��ӡ��������
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
		printf("��ѯʧ��");
	}
}
void borrowbook(MYSQL *connect_p,char user_name[100]) {
	char book_name[100], s[200];
	int res = 0;//ִ��SQL����ķ���ֵ
	MYSQL_RES* res_ptr; /*ָ���ѯ�����ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	int row, column; /*��ѯ���ص�����������*/
	int i, j;
	char* str_sql = s;
	char sql[100] = { '\0' };
	char up1[100] = { '\0' };char* update1 = up1;
	char up2[100] = { '\0' };char* update2 = up2;
	printf("������������Ϣ:");
	scanf("%s", book_name);
	strcpy(str_sql, "select book_state,book_id from book where book_name='");
	str_sql = strcat(str_sql, book_name);
	str_sql = strcat(str_sql, "';\0");
	printf("%s", str_sql);
	strcpy(sql, str_sql);
	res = mysql_query(connect_p, sql);
	printf("res=%d\n", res);
	if (!res) {
		printf("���ڲ�ѯ");
		res_ptr = mysql_store_result(connect_p);
		if (res_ptr) {
			result_row = mysql_fetch_row(res_ptr);
			printf("%s", result_row[0]);
			int tmp = atoi(result_row[0]);
			char *book_id = result_row[1];
			mysql_free_result(res_ptr);
			if (tmp == 1) {
				printf("��ͼ���ѱ����\n����ʧ��");
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
					printf("���ĳɹ�");
				}
			}
		}
	}
	else
	{
		printf("����ʧ��");
	}
}
int backbook(MYSQL* connect_p,char user_name[100]) {
	char book_name[100], s[200];
	int res = 0;//ִ��SQL����ķ���ֵ
	MYSQL_RES* res_ptr; /*ָ���ѯ�����ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	int row, column; /*��ѯ���ص�����������*/
	int i, j,isback,flag=1;
	char* str_sql = s;
	char sql[100] = { '\0' };
	char up1[100] = { '\0' };char* update1 = up1;
	char up2[100] = { '\0' };char* update2 = up2;
	printf("������Ҫ�黹��������Ϣ:");
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
				printf("���Ѿ��黹���������");
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
				printf("�黹�ɹ�");
				return 1;
			}
			printf("�黹ʧ��");
			return 0;
		}
		else {
			return 0;
		}
	}
	return 0;
}

void opadmin(char u_name[100],MYSQL *connect_p) {
	printf("\t1......���ͼ��\n");
	printf("\t2......ɾ��ͼ��\n");
	printf("\t3......�޸�ͼ����Ϣ\n");
	printf("\t4......�˳�ϵͳ");
}

int opuser(char u_name[100],MYSQL *connect_p) {
label:
	printf("\n\t----------------------------------------------\t\n");
	printf("\t1......����ͼ��.....\n");
	printf("\t2......�黹ͼ��.....\n");
	printf("\t3......��ѯͼ��.....\n");
	printf("\t4......�˳�ϵͳ.....\n");
	int tmp = 0;
	scanf("%d", &tmp);
	switch(tmp) {
		case 4: printf("���˳�ϵͳ\n");return 0;
		case 3: printf("���Ե�\n"); select_book(connect_p);break;
		case 1: printf("���Ե�\n");borrowbook(connect_p,u_name);break;
		case 2: printf("���Ե�\n");backbook(connect_p, u_name);break;
	}
	goto label;

}
int main() {
	MYSQL connect;
	char u_name[100], u_pwd[100],s[100];
	char *str_sql=s;
	int res;//ִ��SQL����ķ���ֵ
	char sql[200], ch;
	MYSQL_RES* res_ptr; /*ָ���ѯ�����ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	int row, column; /*��ѯ���ص�����������*/
	int i, j, admin = 0;
	//��ʼ���������ݿ�
	mysql_init(&connect);

	//ʵ���������ݿ�s
	if (mysql_real_connect(&connect, "localhost", "root", "123456", "test", 0, 0, 0)) {
		printf("���ӳɹ�\n��ӭʹ��ͼ�����ϵͳ\n");
		//���ñ����ʽ
		mysql_query(&connect, "set names gbk;");
//----------------------------------------------�ָ���-----------------------------
	lable:	
		printf("����������˺�:");scanf("%s", u_name);
		printf("�������������:");scanf("%s", u_pwd);
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
					printf("�����������û�������\n");
					goto lable;
				}
				int tmp = atoi(result_row[0]);
				//��ӡ��������
				printf("\n");
				if ( tmp == 1) {
					printf("��ӭ����Ա%s��¼", u_name);
					admin = 1;
				}
				else if (tmp == 0) {
					printf("��ӭ�û�%s��¼", u_name);
				}
			}
			mysql_free_result(res_ptr);
		}
		printf("\n\n");
//---------------------------------------------------------�ָ���----------------------------------------------
		strcpy(sql,"select book_id 'ͼ����',book_name 'ͼ����',book_auth '����',book_state 'ͼ���Ƿ��Ѿ����' from book");
		res = mysql_query(&connect, sql);
		if (!res) {
			res_ptr = mysql_store_result(&connect);
			if (res_ptr) {
				column = mysql_num_fields(res_ptr);
				row = mysql_num_rows(res_ptr)+1;
				//��ӡ����
				for (i = 0;(field = mysql_fetch_fields(res_ptr)+i) && i<column;i++) {
					printf("\t%10s\t", field->name);
				}
				//��ӡ��������
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
		printf("ͼ�����ϵͳ����ʧ��\n�Ѿ��˳�ϵͳ");
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