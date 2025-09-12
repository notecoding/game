 #include<stdio.h>
 #include<conio.h>
 #include<windows.h>
 #defineX_MAX 79  //가로(열)방향의최대값
#defineY_MAX 24  //세로(행)방향의최대값
void move_arrow_key(char chr, int*x, int*y, intx_b, inty_b);
 void gotoxy(intx, inty);
 int main(void)
 {
 char key;
 intx=10, y=5;
 do
 {
 gotoxy(x, y);
 printf("A");
 key=getch();
 move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
 }while(key!=27);
 return 0;
 }
