#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define wideth 9
#define height 9

char hide[wideth][height];
char show[wideth][height];
int boom_num;//���׸���

//��ʼ����Ϸ
void start(){
    int i,j,x,y,flag;
    for(i=0;i<wideth;i++){
        for(j=0;j<height;j++){
            hide[i][j]='0';
            show[i][j]='*';
        }
    }

    //������ӵ��׵�hide��
    while(1){
        x= rand()% wideth +1;
        y= rand()% height +1;
        if(hide[x][y] != '1'){
            hide[x][y]='1';
            flag++;
        }
        if(flag==boom_num){
            break;
        }
    }
}

//չʾ��ǰ��show��
void Show(){
    int i,j;
    for(i=0;i<wideth;i++){
        putchar('\n');
        for(j=0;j<height;j++){
            printf(" %c ",show[i][j]);
        }
    }
}
int get_num(int x,int y){
    int n=0;
    if(hide[x-1][y-1]=='1'){
        n++;
    }
    if(hide[x][y-1]=='1'){
        n++;
    }
    if(hide[x+1][y-1]=='1'){
        n++;
    }
    if(hide[x-1][y]=='1'){
        n++;
    }
    if(hide[x+1][y]=='1'){
        n++;
    }
    if(hide[x-1][y+1]=='1'){
        n++;
    }
    if(hide[x][y+1]=='1'){
        n++;
    }
    if(hide[x+1][y+1]=='1'){
        n++;
    }
    return n;
}
void updateShow(int x,int y){
    if(hide[x][y]=='1'){
        printf("��Ϸ����,������");
        exit(-1);
    }
    else{
        show[x][y]=get_num(x,y);
        Show();
    }
}
int main()
{
    int x,y;
    
}