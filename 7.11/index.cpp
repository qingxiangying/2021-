#include<stdio.h>
#include "1.cpp"
#include "2.cpp"
#include "3.cpp"
//#include "4.cpp"
#include "5.cpp"
int main()
{
    int p=0;
    int score=0;
label: 
    score=0;
    printf("请选择你的操作\n");
    printf("1.....飞机大战\n");
    printf("2.....扫    雷\n");
    printf("3.....2 0  4 8\n");
   // printf("4.....贪 吃 蛇\n");
    printf("5.....2  1  点\n");
    printf("6.....退    出\n");
    scanf("%d",&p);
    switch(p){
        case 1: score=game_1_plane();break;
        case 2: score=game_2_mineClearance();break;
        case 3: score=game_3_2048();break;
        //case 4: score=game_4_snake();break;
       case 5: score=game_5_heyjack();break;
        case 6: printf("已经退出系统");exit(-1);break;
    }
    printf("你的得分是:%d\n",score);
    goto label;
    

}