#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct StudentInfo{
    int sid;
    char sname[100];
    char ssex[100];
    int sage;
};
struct ClassInfo{
    int classId;
    int classNum;
    struct StudentInfo student[100];
};
struct School{
    int schoolNum;
    struct ClassInfo Class[100]; 
}s;

void addStuden(){
    int id,age,classid;
    char name[100];char sex[100];
    printf("��ѧ��¼���ĸ��༶");scanf("%d",&classid);
    printf("��ѧ����ѧ��:");scanf("%d",&id);
    printf("��ѧ��������:");scanf("%s",name);
    printf("��ѧ��������:");scanf("%d",&age);
    printf("��ѧ�����Ա�:");scanf("%s",sex);
    s.Class[classid].student[s.Class[classid].classNum].sid=id;
    strcpy( s.Class[classid].student[s.Class[classid].classNum].sname,name);
    strcpy( s.Class[classid].student[s.Class[classid].classNum].ssex,sex);
    s.Class[classid].student[s.Class[classid].classNum].sage=age;
}

void getSchoolInfo(){
    int i,j;
    for(i=0;i<s.schoolNum;i++){
        printf("�༶:%d................................\n",s.Class[i].classId);
        for(j=0;j<s.Class[i].classNum;j++){
            printf("%d\t",s.Class[i].student[j].sid);
            printf("%s\t",s.Class[i].student[j].sname);
            printf("%s\t",s.Class[i].student[j].ssex);
            printf("%d\n",s.Class[i].student[j].sage);
        }
    }
}
void getStudentInfoByid(int id){
    int flag=0;
    for(int i=0;i<s.schoolNum;i++){
        if(flag==1){
            break;
        }
        for(int j=0;j<s.Class[i].classNum;j++){
            if(s.Class[i].student[j].sid == id){
                printf("�༶:%d\t",s.Class[i].classId);
                printf("ѧ��:%d\t",s.Class[i].student[j].sid);
                printf("����:%s\t",s.Class[i].student[j].sname);
                printf("�Ա�:%s\n",s.Class[i].student[j].ssex);
                flag=1;
                break;
            }
        }
    }
}
void delStudentByid(int id){
    int flag=0;
    for(int i=0;i<s.schoolNum;i++){
        if(flag==1){
            break;
        }
        for(int j=0;j<s.Class[i].classNum;j++){
            if(s.Class[i].student[j].sid == id){
                s.Class[i].student[j]=s.Class[i].student[s.Class[i].classNum];
                s.Class[i].classNum--;
                flag=1;
                break;
            }
        }
    }
}
void fixStudentInfoByid(int id){
    int flag=0;
    char ch[100];
    int age;
    for(int i=0;i<s.schoolNum;i++){
        if(flag==1){
            break;
        }
        for(int j=0;j<s.Class[i].classNum;j++){
            if(s.Class[i].student[j].sid == id){
                printf("�������µ���Ϣ....\n");
                printf("ѧ��ѧ��:");scanf("%d",&s.Class[i].student[j].sid);
                printf("ѧ������:");scanf("%s",ch);
                strcpy(s.Class[i].student[j].sname,ch);memset(ch,'\0',100);
                printf("ѧ������:");scanf("%d",&s.Class[i].student[j].sage);
                printf("ѧ���Ա�:");scanf("%s",ch);
                strcpy(s.Class[i].student[j].ssex,ch);
                flag=1;
                break;
            }
        }
    }
}
void sortByid(){
    struct StudentInfo tmp;
    for(int i=0;i<s.schoolNum;i++){
        for(int j=0;j<s.Class[i].classNum;j++){
            for(int k=j;k<s.Class[i].classNum;k++){
                if(s.Class[i].student[j].sid > s.Class[i].student[k].sid){
                    tmp=s.Class[i].student[j];
                    s.Class[i].student[j]=s.Class[i].student[k];
                    s.Class[i].student[k]=tmp;
                }
            }
        }
    }
}
int main()
{
    int a=0,i,j,b=0;
    int id;
    char ch[100];
    printf("����ѧУ:.....0������.......1�˳�: ");scanf("%d",&a);
    if(a==1){
        printf("�Ѿ��˳�\n");
        exit(-1);
    }
    s.schoolNum=0;
    printf("ΪѧУ�������ٸ��༶\n");scanf("%d",&a);
    printf("��������Щ�༶��id:\n");
    for(i=0;i<a;i++){
        scanf("%d",&s.Class[i].classId);
        s.Class[i].classNum=0;
        s.schoolNum++;
    }
    for(i=0;i<a;i++){
        printf("ΪidΪ%d�İ༶��ʼ������ѧ��\n",s.Class[i].classId);
        j=0;
        while(1){
            printf("ѧ��ѧ��:");scanf("%d",&s.Class[i].student[j].sid);
            printf("ѧ������:");scanf("%s",ch);
            strcpy(s.Class[i].student[j].sname,ch);memset(ch,'\0',100);
            printf("ѧ������:");scanf("%d",&s.Class[i].student[j].sage);
            printf("ѧ���Ա�:");scanf("%s",ch);
            strcpy(s.Class[i].student[j].ssex,ch);
            s.Class[i].classNum++;j++;

            printf("�Ƿ����Ϊ�ð༶����:��������.....0  �˳�......1: ");scanf("%d",&b);
            if(b==1){
                break;
            }
        }
    }
    printf("��ʼ����ɣ���ѡ�����Ĳ���..\n");
lable:
    printf("\t.|1.¼��ѧ��..................|\n");
    printf("\t.|2.�鿴ѧУ��Ϣ..............|\n");
    printf("\t.|3.����ѧ��--����ѧ��........|\n");
    printf("\t.|4.����ѧ��--����ѧ��........|\n");
    printf("\t.|4.�޸���Ϣ--����ѧ��........|\n");
    printf("\t.|5.���༶��ѧ������������Ϣ.|\n");
    scanf("%d",&a);  
    switch (a)
    {
    case 1:
        addStuden();
        break;
    
    case 2:
        getSchoolInfo();
        break;
    case 3:
        printf("�����������ѧ����ѧ��:");scanf("%d",&id);
        getStudentInfoByid(id);
        break;
    case 4:
        printf("��������Ҫ������ѧ����ѧ��:");scanf("%d",&id);
        delStudentByid(id);
        break;
    case 5:
        sortByid();
        getSchoolInfo();
        break;
    }
    printf("�Ƿ��ٴβ�������.......0  ��......1: ");
    scanf("%d",&a);
    if(a==1){
        goto lable;
    }
    printf("�Ѿ��˳�ϵͳ\n");

}