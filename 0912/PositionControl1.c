void gotoxy(int x,int y){
    COORD pos={x-1,y-1};
    SetConsoleCursorposition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}