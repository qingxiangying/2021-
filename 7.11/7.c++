#include<stdio.h>
#include<math.h>

char show[3][3]={' '};
//��ӡ����
void show_stage(){

    //��ӡ�ϱ߽�
    for(int i=0;i<3;i++){
        printf("+");
        for(int j=0;j<3;j++){
            printf("-");
        }
    }
    printf("+");


}

int main()
{
    printf("��ӭ����������\n");
    show_stage();
}