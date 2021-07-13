#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//��Ϸ����
#define FrameX 4   //��Ϸ�������Ͻǵ�X������
#define FrameY 4   //��Ϸ�������Ͻǵ�Y������
#define Frame_height  20 //��Ϸ���ڵĸ߶�
#define Frame_width   20 //��Ϸ���ڵĿ��

//����ȫ�ֱ���
static int i,j;
static int a[2];     //���ڼ�ס��β���꣬����a[0]��a[1]�ֱ��ʾ�ᡢ������
static int score4;
//�����ߵĽṹ��
 struct Snake
{
 int x[100];    //�ߵĺ����꣬����x[0]��ʾ��β�ĺ����꣬x[N-1]��ʾ��ͷ�ĺ�����
 int y[100];    //�ߵ������꣬����y[0]��ʾ��β�������꣬y[N-1]��ʾ��ͷ��������
 int count;    //�߳�ʳ��ĸ���
 int length;    //�ߵĳ���
 int speed;    //�ߵ��ٶ�
};

//����ʳ��Ľṹ��
 struct Food
{
 int x;     //ʳ��ĺ�����
 int y;     //ʳ���������
};
 
/******����Ƶ�ָ��λ��**************************************************************/
static void gotoxy(HANDLE hOut, int x, int y)
{
 COORD pos;
 pos.X = x;  //������
 pos.Y = y;  //������
 SetConsoleCursorPosition(hOut, pos);
}

/******�����ı�Ϊ��ɫ*****************************************************************/
static void Set_TextColor_Green (void)
{ 
 HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
 
 SetConsoleTextAttribute(Handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}

/******������Ϸ����******************************************************************/
static void make_frame()
{
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //������ʾ���������
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+13);  //��ӡѡ��˵�
 printf("Esc �˳���Ϸ");
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+15);
 printf("���������������");

 gotoxy(hOut,FrameX,FrameY);       //��ӡ���
 printf("�X");
 gotoxy(hOut,FrameX+2*Frame_width-2,FrameY);
 printf("�[");
 gotoxy(hOut,FrameX,FrameY+Frame_height);
 printf("�^");
 gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+Frame_height);
 printf("�a");
 for(i=2;i<2*Frame_width-2;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY);
  printf("�T");         //��ӡ�Ϻ��
 }
 for(i=2;i<2*Frame_width-2;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY+Frame_height);
  printf("�T");         //��ӡ�º��
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX,FrameY+i); 
  printf("�U");         //��ӡ������s
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+i); 
  printf("�U");         //��ӡ������
 }

 gotoxy(hOut,FrameX+Frame_width-5,FrameY-2);   //��ӡ��Ϸ���� 
 Set_TextColor_Green ();        //������Ϊ��ɫ
 printf("̰������Ϸ");
}

/******�����˵�*******************************************************************/
static void over_game()
{
 system("cls");
 printf("\n\n\n\n\n\n\n\n\t\t\t\t��Ϸ����\n\n\n");
 Sleep(2000);
 getch();
}

/******�˵���Ϣ***************************************************************/
static void print_information(HANDLE hOut,struct Snake *snake,struct Food *food)
{
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+1);
 printf("level : %d",snake->count/5+1);    //��ӡ��Ϸ�ȼ�
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+3);
 printf("score : %d",10*snake->count);score4=10*snake->count;    //��ӡ��Ϸ�÷�
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+5);
 printf("eat food : %d",snake->count);    //��ӡ����ʳ����� 
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+7);
 printf("speed : %dms",snake->speed);    //��ӡ��Ϸ�ٶ�
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+9);
 printf("foodX : %d",food->x);      //��ӡʳ��ĺ�����
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+11);
 printf("foodY : %d",food->y);      //��ӡʳ���������
}

/******��ʼ����**********************************************************************/
static void init_snake(struct Snake *snake)
{
 snake->x[0]=FrameX+2;     //��ʼ���ߵĺ�����
 snake->y[0]=FrameY+Frame_height/2;  //��ʼ���ߵ�������
 snake->speed=300;      //��ʼ���ߵ��ٶ�Ϊ300ms
 snake->length=3;      //��ʼ���ߵĳ���Ϊ3��
 snake->count=0;       //��ʼ���߳Եĸ���Ϊ0
 for(i=1;i<snake->length;i++)
 {/* ���εõ�������ͷ������ */
  snake->x[i]=snake->x[i-1]+2;
  snake->y[i]=snake->y[i-1];
 } 
}

/******�ƶ���*************************************************************************/
static void move_snake(HANDLE hOut,struct Snake *snake)
{
 gotoxy(hOut,snake->x[0],snake->y[0]);
 printf("  ");       /* �����β*/
 for(i=1;i<snake->length;i++)
 {/* ��һ�ڵ���������ȡ��ǰһ�ڵ����� */
  snake->x[i-1]=snake->x[i];
  snake->y[i-1]=snake->y[i];
 }
}

/******��ӡ��*************************************************************************/
static void print_snake(HANDLE hOut,struct Snake *snake)
{
 for(i=0;i<snake->length;i++)
 {
  gotoxy(hOut,snake->x[i],snake->y[i]);
  if(i==0)
  {
   printf("��");       //��ӡ��β
  }
  else if(i==snake->length-1)
  {
   printf("��");       //��ӡ��ͷ
  }
  else
  {
   printf("��");       //��ӡ����
  }
 }
}

/******�������ʳ��*******************************************************************/
static void get_food(HANDLE hOut,struct Snake *snake,struct Food *food)
{
 srand((unsigned)time(NULL));       //��ʼ�������
 while(1)
 {/* ����ʳ���������1.����Ϸ������ 2.�����ߵ����� */ 
  food->x = rand() % (Frame_width-1);
  food->y = rand() % Frame_height;
  if( food->x==0 || food->y==0 )
  {
   continue;
  }
  food->x = 2*food->x + FrameX;      //�õ�ʳ��ĺ�����
  food->y+=FrameY;         //�õ�ʳ���������
  for(i=0;i<snake->length;i++)
  {/* �ж�ʳ���Ƿ����ߵ����ϣ�����������ϣ������²��������򣬴�ӡ���� */
   if( food->x==snake->x[i] && food->y==snake->y[i] )
   {
    break;
   }
  }
  if(i==snake->length)
  {
   gotoxy(hOut,food->x,food->y);
   printf("��");
   break;
  } 
 }
}

/******��ʳ��***************************************************************************/
static void eat_food(HANDLE hOut,struct Snake *snake,struct Food *food)
{
 if( snake->x[snake->length-1]==food->x && snake->y[snake->length-1]==food->y )
 {/* �����ͷλ����ʳ��λ����ͬ����ʳ�� */
  snake->length++;      //��һ��ʳ���������һ��
  for(i=snake->length-1;i>=1;i--)
  {/* �ߺ���������θ�ֵ����ǰһ�ڵ����꣬���εõ�������ͷ������ */
   snake->x[i]=snake->x[i-1];
   snake->y[i]=snake->y[i-1];
  } 
  snake->x[0]=a[0];      //�õ���β�ƶ�ǰ�ĺ�����
  snake->y[0]=a[1];      //�õ���β�ƶ�ǰ��������  
  get_food(hOut,snake,food);    //���²���ʳ��
  snake->count++;       //ʳ��ĸ�����1
  if( snake->count%5==0 && snake->speed >50 )
  {/* ���߳�Up_level��ʳ��ʱ���ٶȼӿ�Up_speed���벢����һ�� */
   snake->speed-=50;
  }
 }
}

/******��ǽ**********************************************************************************/
static void through_wall(HANDLE hOut,struct Snake *snake,char ch)
{
 if( ch==72 && snake->y[snake->length-1]==FrameY)
 {
  snake->y[snake->length-1] = FrameY+Frame_height-1; //��������Ͽ��������ƶ�����ǽ
 }
 if( ch==80 && snake->y[snake->length-1]==FrameY+Frame_height )
 {
  snake->y[snake->length-1] = FrameY+1;    //��������¿��������ƶ�����ǽ
 }
 if( ch==75 && snake->x[snake->length-1]==FrameX )
 {
  snake->x[snake->length-1] = FrameX+2*Frame_width-4; //�����������������ƶ�����ǽ
 }
 if( ch==77 && snake->x[snake->length-1]==FrameX+2*Frame_width-2 )
 {
  snake->x[snake->length-1] = FrameX+2;    //��������ҿ��������ƶ�����ǽ
 }
}

/******�ж����Ƿ���**************************************************************************/
static int if_die(struct Snake *snake)
{/* ����ͷ��������ʱ������ ������ֵΪ0 */
 for(i=0;i<snake->length-1;i++)
 {
  if( snake->x[snake->length-1]==snake->x[i] && snake->y[snake->length-1]==snake->y[i] )
  {
   return 0;
  }
 }
 return 1;
}

/******��ʼ��Ϸ*******************************************************************************/
static void start_game()
{
system("cls");
 unsigned char ch=77;        //�������ڽ��ռ���������ַ�����
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //������ʾ���������
 struct Snake s,*snake=&s;      //�����ߵĽṹ��ָ�벢ָ���ߵĽṹ��
 struct Food f,*food=&f;       //����ʳ��Ľṹ��ָ�벢ָ��ʳ��Ľṹ��
 
 make_frame();         //������Ϸ���� 
 init_snake(snake);        //��ʼ����
 get_food(hOut,snake,food);      //�������ʳ��
 while(1)
 {
  print_information(hOut,snake,food);   //��ӡ�˵���Ϣ
  a[0]=snake->x[0];       //��ס��β�ĺ�����
  a[1]=snake->y[0];       //��ס��β��������
  j=0;
  if(kbhit())
  {/* �ж��Ƿ��¼��̣�������£�ch���ռ������� */
   ch=getch();
   if(kbhit())
   {/* ����������̣������ */
    Sleep(20);
    j=1;
   }
  }
  switch(ch)
  {
   case 72:
    {/* �����ƶ� */
     move_snake(hOut,snake);   //�ƶ���
     snake->y[snake->length-1]-=1; //��ͷ�������������ƣ�����1
     break;
    }
   case 80:
    {/* �����ƶ� */
     move_snake(hOut,snake);   //�ƶ���
     snake->y[snake->length-1]+=1; //��ͷ�������������ƣ�����1
     break;
    }
   case 75:
    {/* �����ƶ� */
     move_snake(hOut,snake);   //�ƶ���
     snake->x[snake->length-1]-=2; //��ͷ�ĺ����������ƣ�����2
     break;
    }    
   case 77:
    {/* �����ƶ� */
     move_snake(hOut,snake);   //�ƶ���
     snake->x[snake->length-1]+=2; //��ͷ�ĺ����������ƣ�����2
     break;
    }
  }
  through_wall(hOut,snake,ch);    //��ǽ   
  eat_food(hOut,snake,food);     //��ʳ��
  print_snake(hOut,snake);     //��ӡ��
  if( if_die(snake)==0 || ch==27 || snake->speed<50 )
  {/* ��Ϸ����������1.���������� 2.��Esc�� 3.�ٶ�Ϊ50ms */
   gotoxy(hOut,FrameX+Frame_width-2,FrameY+Frame_height/2-1);
   printf("Game Over");
   Sleep(2000);
   break;
  }
  if(j==0)
  {
   Sleep(snake->speed);      //�ӳ�ʱ��
  }
  else
  {
   Sleep(10);
  } 
 }
}
int main()
{
 system("color 0D");  //�����ı�Ϊ�ۺ�ɫ

 start_game();   //��ʼ��Ϸ

 over_game();   //������Ϸ
 return score4;
}
