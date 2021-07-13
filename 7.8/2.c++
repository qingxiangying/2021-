#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define wideth 9
#define height 9

char hide[wideth][height];
char show[wideth][height];
int boom_num;//地雷个数

//初始化游戏
void start(){
    int i,j,x,y,flag;
    for(i=0;i<wideth;i++){
        for(j=0;j<height;j++){
            hide[i][j]='0';
            show[i][j]='*';
        }
    }

    //随机增加地雷到hide中
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

//展示当前的show阵
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
        printf("游戏结束,你输了");
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