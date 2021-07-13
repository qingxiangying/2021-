#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")

#define HIGH 20  //游戏界面高度
#define WIDTH 30  // 游戏界面宽度
//#define NUM 10  //敌机下落速度
//int flag=0;
static struct Plane {
    int p;
    int isdeath;
    int position_x;
    int position_y;
    int bullet_x;
    int bullet_y;
    int enemy_x;
    int enemy_y;
}plane;
static int score_plane;  //得分

static int speed = 0;
static int NUM = 10, vt;
static int k;
static int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
    return 0;
}
static void gotoxy(int x, int y) //将光标调整到(x,y)的位置
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

static void HideCursor()  //隐藏光标显示
{
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

static void startup()//数据的初始化
{
    //初始化飞机
    plane.position_x = HIGH / 2; //高度
    plane.position_y = WIDTH / 2; //宽度

    //初始化子弹
    plane.bullet_x = -1;
    plane.bullet_y = plane.position_y;

    //初始化敌机
    plane.enemy_x = 0;
    plane.enemy_y = plane.position_y;

    //初始化得分
    score_plane = 0;
    plane.isdeath=0;
}

static void show()//显示画面
{
    int i, j;
    // system("cls"); //清屏函数  
    gotoxy(0, 0); //使光标回到0，0


    for (i = 0; i < HIGH; i++) //行
    {
        for (j = 0; j < WIDTH; j++) //列
        {
            if (i == plane.position_x && j == plane.position_y)//输出飞机
            {
                printf("Ж");
            }
            else if (i == plane.bullet_x && j == plane.bullet_y)//输出子弹
            {
                printf("|");
            }
            else if (i == plane.enemy_x && j == plane.enemy_y)//输出敌机
            {
                printf("Ψ");
            }
            else if ((j == WIDTH - 1) || (i == HIGH - 1) || (j == 0) || (i == 0))				//打印边界 
                printf("-");
            else
            {
                printf(" ");
            }
        }
        if ((plane.position_x == plane.enemy_x) && (plane.position_y == plane.enemy_y))
        {
            //飞机撞毁 游戏结束 
            system("cls");
            gotoxy(43, 15);
            printf("你挂了，游戏结束!!!\n");
            plane.isdeath = 1;

        }
        printf("\n");
    }

}
static void updateWitoutIput_1()//与用户输入无关的更新
{
    if (plane.bullet_x > -1) //让子弹向上落
    {
        plane.bullet_x--;
    }
    if (plane.bullet_x == plane.enemy_x && plane.bullet_y == plane.enemy_y) //命中敌机
    {
        score_plane += vt * 2;  //得分+1

        plane.enemy_x = -1;   //生成新的飞机
        plane.enemy_y = rand() % (WIDTH-1);

        plane.bullet_x = -1;  //让子弹直接出现屏幕外，直到下一次发射子弹
    }

    //控制敌机下落速度
    if (speed < NUM)  //每进行NUM次敌机下落一次
    {
        speed++;
    }
    else
    {
        plane.enemy_x++;
        speed = 0;
    }
    if (plane.enemy_x > HIGH)  //敌机一直下落到底部
    {
        plane.enemy_x = -1;
        plane.enemy_y = rand() % WIDTH;
    }

}
static void updateWithInput()//与用户输入有关的更新
{
    //用户输入
    char input;//控制飞机飞行
    if (_kbhit())
    {
        input = _getch();
        if (input == 'w' && plane.position_x > 1)
            plane.position_x--;
        if (input == 's' && plane.position_x < HIGH - 1)
            plane.position_x++;
        if (input == 'a' && plane.position_y > 1)
            plane.position_y--;
        if (input == 'd' && plane.position_y < WIDTH - 1)
            plane.position_y++;
        if (input == ' ')
        {
            plane.bullet_x = plane.position_x - 1;
            plane.bullet_y = plane.position_y;
        }
    }
}
static void moden()//设置难度
{
    if (vt == 3)
        NUM = 5;
    else if (vt == 2)
        NUM = 15;
    else if (vt == 1)
        NUM = 25;
    else if (vt == 4)
        NUM = 1;
    else if (vt==5)
        NUM= 100;
    else
    {
        
        printf("不要太皮\n");
        exit(0);
    }
}
static void scoreandtips()//游戏侧边提示 
{
    gotoxy(50, 8);
    color(14);
    printf("游戏得分：%d ", score_plane);
    gotoxy(50, 10);
    printf("用W A S D 分别控制飞机的移动");
    gotoxy(50, 12);
    printf("按下空格键即为发射炮弹");
    gotoxy(50, 14);
    printf("Ж  的样子就是敌人的飞机");
    gotoxy(50, 16);
    printf("撞击会死亡哦");
    gotoxy(50, 18);

}
static void appearance()
{
    system("mode con cols=120 lines=30");
    color(15);
    gotoxy(43, 10);
    printf("    飞 机 大 战       \n");
    color(11);
    gotoxy(42, 12);
    printf("欢迎来到飞机大战 请选择模式\n");
    gotoxy(45, 14);
    printf("  1.正常模式    \n");
    gotoxy(45, 15);
    gotoxy(45, 16);
    gotoxy(45, 17);
    gotoxy(42, 18);
    printf("提示：W A S D 移动，空格发射子弹\n");
    gotoxy(45, 1);
    printf("ps:大佬们别挑刺");
    gotoxy(45, 20);
    scanf("%d", &plane.p);

}
static void ssb()
{
    system("cls");
    gotoxy(45, 10);
    printf("别皮！认真玩游戏\n");
    gotoxy(45, 12);
    printf("还想玩请输入666");
    gotoxy(45, 14);
    scanf("%d", &k);
    if (k == 666)
    {
        gotoxy(45, 16);
        color(11);
        printf("哈");
        color(12);
        printf("哈");
        color(13);
        printf("哈");
        color(10);
        gotoxy(45, 17);
        printf("皮一下很开心");
        color(14);
    }
}

static int game_1_plane()
{
    appearance();
    if (plane.p == 1)
    {
        gotoxy(0, 0);
        system("cls");
        color(6);
        gotoxy(43, 10);
        printf("请输入难度\n");
        gotoxy(43, 11);
        printf("1.简单\n");
        gotoxy(43, 12);
        printf("2.普通\n");
        gotoxy(43, 13);
        printf("3.困难\n");
        gotoxy(43, 14);
        scanf("%d", &vt);
        moden();//选择模式
        system("cls");
        startup();//初始化
        HideCursor();
        srand((unsigned)time(NULL));
        while (1)  //循环执行
        {
            gotoxy(0, 0);
            scoreandtips();
            show();//显示画面   
            updateWitoutIput_1();//与用户输入无关的更新  更新数据 
            updateWithInput(); //与用户输入有关的更新  输入分析 
            if (plane.isdeath == 1) {
                plane.isdeath=0;
                break;
            }
        }
        system("pause");
        printf("你的最终得分是:%d", score_plane);
        return score_plane;

    }
    else
        ssb();
    
    return score_plane;

}