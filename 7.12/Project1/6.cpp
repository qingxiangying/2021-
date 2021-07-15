#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<graphics.h> //����easyxͼ�ο��ļ�
#include<time.h>     //C����ʱ��ͷ�ļ�
#include<mmsystem.h>//win32��ý���豸�ӿ��ļ�
#pragma comment(lib,"winmm.lib")//win32��ý���豸�ӿڿ�
#define WIN_WIDTH  1024  //��Ļ�Ŀ�
#define WIN_HEIGHT 640//576   //��Ļ��
#define MAP_WIDTH  (WIN_WIDTH*3) //��ͼ���
#define MAP_HEIGHT (WIN_HEIGHT*3)//��ͼ�߶�
#define FOOD_NUM 500  //ʳ������
#define AI_NUM 200    //ai����
IMAGE map(MAP_WIDTH, MAP_HEIGHT);
POINT  g_CameraPos;      // �����(��Ļ���Ͻ�)�ڵ�ͼ�ϵ�λ��
struct Ball
{
    bool    flag;    // �Ƿ񱻳� �� 1,�� 0
    COLORREF  color;    // ��ɫ
    float    r;      //
    float    x;      // ����
    float    y;
    int      type;       //ʳ��������ԣ�������ʲô���͵�ʳ�Բ�����Σ�����Σ���
};
struct Ball mover; //���
struct Ball food[FOOD_NUM]; //ʳ������
struct Ball ai[AI_NUM]; //AI����
void ChaseAlgorithom(Ball* chase, Ball* run);
float DisTance(Ball b1, Ball b2);
void Gameinit()
{
    //�������������
    srand((unsigned)time(NULL));
    //��ʼ��ʳ��
    for (int i = 0; i < FOOD_NUM; i++)
    {
        food[i].x = (float)(rand() % MAP_WIDTH);
        food[i].y = (float)(rand() % MAP_HEIGHT);
        food[i].r = (float)(rand() % 5 + 1);
        food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);  // �����ɫ
        food[i].flag = 1;
        food[i].type = rand() % 3;
    }
    //��ʼ��AI
    for (int i = 0; i < AI_NUM; i++)
    {
        ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);   //rand()%256  ���ȡֵ 0-255
        ai[i].flag = 1;
        ai[i].x = rand() % (MAP_WIDTH - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);   //AI������λ�ò������һ��Խ��
        ai[i].y = rand() % (MAP_HEIGHT - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);
        ai[i].r = float(rand() % 10 + 10);
    }
    {//��ʼ���������
        mover.color = BLUE;
        mover.r = 10;
        //����ڴ��ڵ�λ��
        mover.x = rand() % WIN_WIDTH;
        mover.y = rand() % WIN_HEIGHT;
        mover.flag = 1;
    }
}
//��Ϸ��ͼ��ʼ����λ���ж�
void computeCameraPos()
{
    // ������λ��Ϊ���ļ��������������λ��
    g_CameraPos.x = mover.x - WIN_WIDTH / 2;
    g_CameraPos.y = mover.y - WIN_HEIGHT / 2;

    // ��ֹ�����Խ��
    if (g_CameraPos.x < 0)    g_CameraPos.x = 0;
    if (g_CameraPos.y < 0)    g_CameraPos.y = 0;
    if (g_CameraPos.x > MAP_WIDTH - WIN_WIDTH)  g_CameraPos.x = MAP_WIDTH - WIN_WIDTH;
    if (g_CameraPos.y > MAP_HEIGHT - WIN_HEIGHT)  g_CameraPos.y = MAP_HEIGHT - WIN_HEIGHT;
}
//��Ϸ����
void Gamedraw()
{
    SetWorkingImage(&map);
    setbkcolor(WHITE);          // ��ɫ����
    cleardevice();
    //��ʳ��
    for (int i = 0; i < FOOD_NUM; i++)
    {
        if (food[i].flag == 1)
        {
            setfillcolor(food[i].color);
            if (food[i].type == 0)
            {
                solidellipse((int)food[i].x, (int)food[i].y, (int)(food[i].x + food[i].r), (int)(food[i].y + food[i].r));
            }
            else if (food[i].type == 1)
            {
                solidpie((int)food[i].x, (int)food[i].y, (int)(food[i].x + food[i].r), (int)(food[i].y + food[i].r), 0.0, 1.5);
            }
            else
            {
                solidcircle(int(food[i].x), int(food[i].y), int(food[i].r));
            }
        }
        else
        {
            food[i].x = (float)(rand() % MAP_WIDTH);
            food[i].y = (float)(rand() % MAP_HEIGHT);
            food[i].r = (float)(rand() % 5 + 1);
            food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);  // �����ɫ
            food[i].flag = 1;
            food[i].type = rand() % 3;
        }
    }
    //��AI
    for (int i = 0; i < AI_NUM; i++)
    {
        if (ai[i].flag == 1)
        {
            setfillcolor(ai[i].color);
            solidcircle(ai[i].x, ai[i].y, ai[i].r);
        }
        else
        {
            ai[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);   //rand()%256  ���ȡֵ 0-255
            ai[i].flag = 1;
            ai[i].x = rand() % (MAP_WIDTH - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);   //AI������λ�ò������һ��Խ��
            ai[i].y = rand() % (MAP_HEIGHT - int(ai[i].r + 0.5)) + int(ai[i].r + 0.5);
            ai[i].r = float(rand() % 10 + 10);
        }
    }
    //�������
    setfillcolor(RED);
    fillcircle(mover.x, mover.y, mover.r);
    //�����������
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    //settextstyle(20, 0, "����");
    //int twidth = textwidth(pname) / 2;//�������ֿ��Ϊ�˾�����ʾ���������
    //outtextxy(mover.x - twidth, mover.y, pname);
    //�ָ�Ĭ�Ϲ�������������
    SetWorkingImage();
    //���������λ��
    computeCameraPos();
    //�ѵ�ͼ��ʾ��������
    putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &map, g_CameraPos.x, g_CameraPos.y);
}
//����ƶ�������Ϊ����ƶ����ٶȣ���λ���أ�
void Gamemove(int speed)
{
    //��ȡ���̰���
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (mover.y - mover.r > 0)
        {
            mover.y -= speed;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (mover.y + mover.r < MAP_HEIGHT)
        {
            mover.y += speed;
        }
    }
    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        if (mover.x - mover.r > 0)
        {
            mover.x -= speed;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        if (mover.x + mover.r < MAP_WIDTH)
        {
            mover.x += speed;
        }
    }
    //���ײ��ԣ����ո񲻶�����,A��С
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        mover.r += 3;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        if (mover.r > 1)
            mover.r -= 1;
    }
}
//��ҳ�ʳ��
void EatFood()
{
    for (int i = 0; i < FOOD_NUM; i++)
    {
        if (food[i].flag == 1 && DisTance(food[i], mover) < mover.r)
        {
            food[i].flag = 0;
            mover.r += food[i].r / 4;
        }
    }
}
//��ҳ�Ai��Ai�����
void EatAi()
{
    for (int i = 0; i < AI_NUM; i++)
    {
        if (ai[i].flag == 0)
            continue;
        //��ҳ�Ai
        if (DisTance(ai[i], mover) < mover.r - ai[i].r / 3)
        {
            ai[i].flag = 0;
            mover.r += ai[i].r / 4;
            break;//�Ե�һ�����˳�
        }
        //ai�����
        else if (DisTance(ai[i], mover) < ai[i].r - mover.r / 3)
        {
            mover.x = rand() % MAP_WIDTH;
            mover.y = rand() % MAP_HEIGHT;
            ai[i].r += mover.r / 4;
            mover.r = 10;
            break;
        }
    }
}
//AI��ʳ��,AI��Ai
void AiEatFood()
{
    for (int i = 0; i < AI_NUM; i++)
    {
        if (ai[i].flag == 0)
            continue;
        //ai��ʳ��
        for (int j = 0; j < FOOD_NUM; j++)
        {
            if (food[j].flag == 1 && DisTance(ai[i], food[j]) < ai[i].r)
            {
                food[j].flag = 0;
                ai[i].r += food[i].r / 4;
            }
        }
        //Ai��Ai
        for (int k = i + 1; k < AI_NUM; k++)
        {
            if (ai[k].flag == 1)
            {
                if (DisTance(ai[i], ai[k]) < ai[k].r - ai[i].r / 3)
                {
                    ai[i].flag = 0;
                    ai[k].r += ai[i].r / 4;
                }
                else if (DisTance(ai[i], ai[k]) < ai[i].r - ai[k].r / 3)
                {
                    ai[k].flag = 0;
                    ai[i].r += ai[k].r / 4;
                }
            }

        }
    }
}
//Ai�ƶ��㷨��׷����Լ��뾶С����
void AiMove()
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
void  JudeEat()
{
    EatFood();
    EatAi();
    AiEatFood();
    AiMove();
}
int main()
{
    initgraph(WIN_WIDTH, WIN_HEIGHT, 1);
    Gameinit();
    DWORD t1, t2;
    t1 = t2 = GetTickCount();
    while (1)
    {
        Gamedraw();
        Gamemove(1);
        if (t2 - t1 > 50)
        {
            JudeEat();
            t1 = t2;
        }
        t2 = GetTickCount();
    }

    getchar();
    closegraph();
    return 0;
}

//׷���㷨
void ChaseAlgorithom(Ball* chase, Ball* run)
{
    if (rand() % 2 == 0)
    {
        if (chase->x < run->x)
        {
            chase->x += 2;
        }
        else
        {
            chase->x -= 2;
        }
    }
    else
    {
        if (chase->y < run->y)
        {
            chase->y += 2;
        }
        else
        {
            chase->y -= 2;
        }
    }
}
//������֮��ľ���
float DisTance(Ball b1, Ball b2)
{
    return sqrt((b1.x - b2.x) * (b1.x - b2.x) + (b1.y - b2.y) * (b1.y - b2.y));
}