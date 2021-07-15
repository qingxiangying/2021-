#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<graphics.h> //����easyxͼ�ο��ļ�
#include<time.h>     //C����ʱ��ͷ�ļ�
#include<mmsystem.h>//win32��ý���豸�ӿ��ļ�
#pragma comment(lib,"winmm.lib")//win32��ý���豸�ӿڿ�
#define WIN_WIDTH  1024  //��Ļ�Ŀ�
#define WIN_HEIGHT 640//576   //��Ļ��
#define MAP_WIDTH  (WIN_WIDTH*3) //��ͼ���
#define MAP_HEIGHT (WIN_HEIGHT*3)//��ͼ�߶�
#define FOOD_NUM 500  //ʳ������
#define AI_NUM 50    //ai����
static IMAGE map_6(MAP_WIDTH, MAP_HEIGHT);
static POINT  g_CameraPos;      // �����(��Ļ���Ͻ�)�ڵ�ͼ�ϵ�λ��

static struct Ball
{
    bool    flag;    // �Ƿ񱻳� �� 1,�� 0
    COLORREF  color;    // ��ɫ
    float    r;      //
    float    x;      // ����
    float    y;
    int      type;       //ʳ��������ԣ�������ʲô���͵�ʳ�Բ�����Σ�����Σ���
};
static struct Ball ai[AI_NUM];
static struct Ball player;
static struct Ball food[FOOD_NUM];
static int reborn = 1;
static int speed_6 = 1;

//����������
static float DisTance(Ball b1, Ball b2)
{
    return sqrt((b1.x - b2.x) * (b1.x - b2.x) + (b1.y - b2.y) * (b1.y - b2.y));
}
static void ChaseAlgorithom(Ball* chase, Ball* run)
{
    if (rand() % 2 == 0)
    {
        if (chase->x < run->x)
        {
            chase->x += 1;
        }
        else
        {
            chase->x -= 1;
        }
    }
    else
    {
        if (chase->y < run->y)
        {
            chase->y += 1;
        }
        else
        {
            chase->y -= 1;
        }
    }
}
//��ʼ����Ϸ
static int initgame_6() {
    srand((unsigned)time(NULL));
    int i, j;
    //��ʼ�����player
    {
        player.flag = 1;
        player.color = RED;
        player.x = rand() % MAP_WIDTH + 1;
        player.y = rand() % MAP_HEIGHT + 1;
        player.r = 10;
    }
    //��ʼ��food
    for (i = 0;i < FOOD_NUM;i++) {
        food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
        food[i].r = rand() % 5;
        food[i].type = rand() % 3;
        food[i].flag = 1;
        food[i].x = rand() % MAP_WIDTH;
        food[i].y = rand() % MAP_HEIGHT;
    }
    //��ʼ��ai
    for (i = 0;i < AI_NUM;i++) {
        ai[i].flag = 1;
        ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
        ai[i].r = rand() % 10;
        ai[i].x = rand() % MAP_WIDTH;
        ai[i].y = rand() % MAP_HEIGHT;
    }

    return 0;
}

//������Ϸ����ǰ��׼��
static int computeCameraPos() {
    // ������λ��Ϊ���ļ��������������λ��
    g_CameraPos.x = player.x - WIN_WIDTH / 2;
    g_CameraPos.y = player.y - WIN_HEIGHT / 2;

    // ��ֹ�����Խ��
    if (g_CameraPos.x < 0)    g_CameraPos.x = 0;
    if (g_CameraPos.y < 0)    g_CameraPos.y = 0;
    if (g_CameraPos.x > MAP_WIDTH - WIN_WIDTH)  g_CameraPos.x = MAP_WIDTH - WIN_WIDTH;
    if (g_CameraPos.y > MAP_HEIGHT - WIN_HEIGHT)  g_CameraPos.y = MAP_HEIGHT - WIN_HEIGHT;

    return 0;
}

//��ӡ��Ϸ����
static int show_6() {
    int i, j;
    SetWorkingImage(&map_6);
    setbkcolor(WHITE);          // ��ɫ����
    cleardevice();
    //����ʳ��
    for (i = 0;i < FOOD_NUM;i++) {
        if (food[i].flag == 1) {
            setfillcolor(food[i].color);//���û���ʱ�����ɫ
            if (food[i].type == 0) {
                solidellipse((int)food[i].x, (int)food[i].y, (int)(food[i].x + food[i].r), (int)(food[i].y + food[i].r));
            }
            else if (food[i].type == 1) {
                solidpie((int)food[i].x, (int)food[i].y, (int)(food[i].x + food[i].r), (int)(food[i].y + food[i].r), 0.0, 1.5);
            }
            else {
                solidcircle((int)food[i].x, (int)food[i].y, (int)food[i].r);
            }

        }
    }

    //����ai
    for (i = 0;i < AI_NUM;i++) {
        if (ai[i].flag == 1) {
            setfillcolor(ai[i].color);
            solidcircle(ai[i].x, ai[i].y, ai[i].r);
        }
        //�˴��趨ai�Ƿ�����
        else if (reborn == 1) {
            ai[i].flag = 1;
            ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
            ai[i].r = rand() % 10;
            ai[i].x = rand() % WIN_WIDTH;
            ai[i].y = rand() % WIN_HEIGHT;
        }
    }

    //�������
    if (player.flag == 1) {
        setfillcolor(player.color);
        solidcircle(player.x, player.y, player.r);
    }
    else if (reborn == 1) {
        player.flag = 1;
        player.color = RED;
        player.x = rand() % WIN_WIDTH + 1;
        player.y = rand() % WIN_HEIGHT + 1;
        player.r = 10;
    }

    //
    SetWorkingImage();
    putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &map_6, g_CameraPos.x, g_CameraPos.y);


    return 0;

}

static void player_move() {
    
// GetAsyncKeyState�ķ���ֵ��ʾ�������ݣ�һ�������λbit��ֵ������������Ƿ񱻰��£�һ�������λbit��ֵ���������ϴε���
// GetAsyncKeyState��������Ƿ񱻰��¡�
    if (GetAsyncKeyState(VK_UP) && 0x8000) {
        player.y -= speed_6;
    }
    if (GetAsyncKeyState(VK_DOWN) && 0x8000) {
        player.y += speed_6;
    }
    if (GetAsyncKeyState(VK_LEFT) && 0x8000) {
        player.x -= speed_6;
    }
    if (GetAsyncKeyState(VK_RIGHT) && 0x8000) {
        player.x += speed_6;
    }
    if (GetAsyncKeyState(VK_SPACE) && 0x8000)
    {
        player.r += 3;
    }
    if (GetAsyncKeyState('A') && 0x8000)
    {
        if (player.r > 1)
            player.r -= 1;
    }
}

//��ҳ�ʳ��
static void EatFood()
{
    for (int i = 0; i < FOOD_NUM; i++)
    {
        if (food[i].flag == 1 && DisTance(food[i], player) < player.r)
        {
            food[i].flag = 0;
            player.r += food[i].r / 4;
        }
    }
}

static void EatAI() {
    int i, j;
    for (i = 0;i < AI_NUM;i++) {
        if ((ai[i].flag == 1 && player.flag == 1) && DisTance(ai[i], player) < (player.r + ai[i].r)) {
            if (player.r > ai[i].r) {
                ai[i].flag = 0;
                player.r += ai[i].r / 4;
            }
            if (player.r <= ai[i].r) {
                player.flag = 0;
                ai[i].r += player.r / 4;
            }
        }
    }
}

static void aiEatAI() {
    int i, j;
    for (i = 0;i < AI_NUM;i++) {
        for (j = 0;j < AI_NUM;j++) {
            if (i == j) {
                continue;
            }
            if (ai[i].flag == 1 && ai[j].flag == 1 && DisTance(ai[i], ai[j]) < (ai[i].r + ai[j].r)) {
                if (ai[i].r >= ai[j].r) {
                    ai[j].flag = 0;
                    ai[i].r += ai[j].r / 4;
                }
                else {
                    ai[i].flag = 0;
                    ai[j].r += ai[i].r / 4;
                }
            }
        }
    }
}

static void aiEatFood() {
    int i, j;
    for (i = 0;i < AI_NUM;i++) {
        for (j = 0;j < FOOD_NUM;j++) {
            if (ai[i].flag == 1 && food[j].flag == 1 && DisTance(ai[i], food[j]) < (ai[i].r)) {
                food[j].flag = 0;
                ai[i].r += food[j].r / 4;
            }
        }
    }
}

static void AiMove()
{
    for (int i = 0; i < AI_NUM; i++)
    {
        double min_DISTANCE = MAP_WIDTH;//�����������
        int min = -1;//���������ҵ�Ŀ��С����±�
        if (ai[i].flag == 1)
        {
            //AI����AI
            for (int k = i + 1; k < AI_NUM; k++)
            {
                if (ai[i].r > ai[k].r && ai[k].flag == 1)
                {//����ܳԣ��Ҿ���ﵽҪ������¾��룬�������±�
                    if (DisTance(ai[i], ai[k]) < min_DISTANCE)
                    {
                        min_DISTANCE = DisTance(ai[i], ai[k]);
                        min = k;
                    }
                }
            }
        }
        //����ҵ�Ŀ�꣬��ȥ׷��
        if ((min != -1))
        {
            ChaseAlgorithom(&ai[i], &ai[min]);
        }

    }
}

static int game_6() {
    int i, j;
    while (1) {
        show_6();
        player_move();
        AiMove();
        computeCameraPos();
        EatFood();
        EatAI();
        aiEatAI();
        aiEatFood();

        if (player.r >= 300) {
            return 1;
        }
        for (i = 0;i < AI_NUM;i++) {
            if (ai[i].r >= 300) {
                return 0;
            }
        }
    }
    return 0;
}

static int game_6_qiuqiu()
{
    int winner = -1;
    initgraph(WIN_WIDTH, WIN_HEIGHT, 1);
    initgame_6();
    winner = game_6();
    Sleep(2000);

    if (winner == 1) {
        printf("��Ӯ��");
    }
    if (winner == 0) {
        printf("������");
    }
    system("pause");

    return player.r;
}