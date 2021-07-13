#include<stdio.h>
#include<math.h>

char show[3][3]={' '};
//¥Ú”°∆Â≈Ã
void show_stage(){

    //¥Ú”°…œ±ﬂΩÁ
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
    printf("ª∂”≠”ŒÕÊ»˝◊÷∆Â\n");
    show_stage();
}