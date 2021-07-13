#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//1是墙
//2是目的地
//3是箱子
//4是人
int map[10][9]={
                {0,0,0,1,1,1,0,0,0},
                {0,0,0,1,2,1,0,0,0},
                {0,0,0,1,0,1,0,0,0},
                {1,1,1,1,3,1,1,1,1},
                {1,2,0,3,4,3,0,2,1},
                {1,1,1,1,3,1,1,1,1},
                {0,0,0,1,0,1,0,0,0},
                {0,0,0,1,0,1,0,0,0},
                {0,0,0,1,2,1,0,0,0},
                {0,0,0,1,1,1,0,0,0}};

void show(){
    int i,j;
    for(i=0;i<10;i++){
        printf("\n");
        for(j=0;j<9;j++){
            switch(map[i][j]){
                case 0 : printf("  ");break;
                case 1 : printf("■ ");break;
                case 2 : printf("☆ ");break;
                case 3 : printf("? ");break;
                case 4 : printf("♂ ");break;
                case 5 : printf("★ "); break;
            }
        }
    }
}

void typeW(){
    int i,j;
    for(i=1;i<9;i++){
        for(j=1;j<8;j++){
            if(map[i][j]==4){
                if(map[i-1][j]==0){
                    map[i][j]=0;
                    map[i-1][j]=4;
                }
                if(map[i-1][j]==3){
                    if(map[i-2][j]==0){
                        map[i-2][j]=3;
                        map[i-1][j]=4;
                        map[i][j]=0;
                    }
                    if(map[i-2][j]==2){
                        map[i-2][j]=5;
                        map[i-1][j]=4;
                        map[i][j]=0;
                    }
                }
            }
        }
    }
}
void typeS(){
    int i,j;
    for(i=1;i<9;i++){
        for(j=1;j<8;j++){
              if(map[i][j]==4){
                if(map[i+1][j]==0){
                    map[i][j]=0;
                    map[i+1][j]=4;
                }
                if(map[i+1][j]==3){
                    if(map[i+2][j]==0){
                        map[i+2][j]=3;
                        map[i+1][j]=4;
                        map[i][j]=0;
                    }
                    if(map[i+2][j]==2){
                        map[i+2][j]=5;
                        map[i+1][j]=4;
                        map[i][j]=0;
                    }
                }
            }
        }
    }
}
void typeA(){
    int i,j;
    for(i=1;i<9;i++){
        for(j=1;j<8;j++){
            if(map[i][j]==4){
                if(map[i][j-1]==0){
                    map[i][j]=0;
                    map[i][j-1]=4;
                }
                if(map[i][j-1]==3){
                    if(map[i][j-2]==0){
                        map[i][j-2]=3;
                        map[i][j-1]=4;
                        map[i][j]=0;
                    }
                    if(map[i][j-2]==2){
                        map[i][j-2]=5;
                        map[i][j-1]=4;
                        map[i][j]=0;
                    }
                }
            }
        }
    }
}
void typeD(){
    int i,j;
    for(i=1;i<9;i++){
        for(j=1;j<8;j++){
            if(map[i][j]==4){
                if(map[i][j+1]==0){
                    map[i][j]=0;
                    map[i][j+1]=4;
                }
                if(map[i][j+1]==3){
                    if(map[i][j+2]==0){
                        map[i][j+2]=3;
                        map[i][j+1]=4;
                        map[i][j]=0;
                    }
                    if(map[i][j+2]==2){
                        map[i][j+2]=5;
                        map[i][j+1]=4;
                        map[i][j]=0;
                    }
                }
            }
        }
    }
}

int isWin(){
    int count=0,i,j;
    for(i=0;i<10;i++){
        for(j=0;j<9;j++){
            if(map[i][j]==5){
                count++;
            }
        }
    }
    if(count==4){
        return 1;
    }
    return 0;
}
int updateWithUser(){
    char ch;
    while(1){
        ch=getchar();
        switch(ch){
            case 'w': typeW(); system("cls"); show(); break;
            case 's': typeS(); system("cls"); show(); break;
            case 'a': typeA(); system("cls"); show(); break;
            case 'd': typeD(); system("cls"); show(); break;
            case 'm': return 0;
        }
        if(isWin()){
            return 1;
        }

    }
    return 0;
}

int main()
{
    int i,j,win;
    system("cls");
    show();
    win=updateWithUser();
    printf("\n");
    if(win==1){
        printf("你赢了");
    }
}