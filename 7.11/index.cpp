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
    printf("��ѡ����Ĳ���\n");
    printf("1.....�ɻ���ս\n");
    printf("2.....ɨ    ��\n");
    printf("3.....2 0  4 8\n");
   // printf("4.....̰ �� ��\n");
    printf("5.....2  1  ��\n");
    printf("6.....��    ��\n");
    scanf("%d",&p);
    switch(p){
        case 1: score=game_1_plane();break;
        case 2: score=game_2_mineClearance();break;
        case 3: score=game_3_2048();break;
        //case 4: score=game_4_snake();break;
       case 5: score=game_5_heyjack();break;
        case 6: printf("�Ѿ��˳�ϵͳ");exit(-1);break;
    }
    printf("��ĵ÷���:%d\n",score);
    goto label;
    

}