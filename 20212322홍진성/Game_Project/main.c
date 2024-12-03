#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void textcolor(int Text_Color, int Background_Color)
//Text_Color는 글자의 색상
//Background_Color는 배경의 색상을 변경
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Text_Color | Background_Color << 4);
}

typedef enum Color { //수업 중에 사용한 컬러 함수를 복붙, 문제시 #define을 이용 
	BLACK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
}COLOR;

int main() {
	srand(time(NULL));
	textcolor(YELLOW, BLACK); //컬러 지정
}

void removeCursor(void) { //마우스 깜빡거리는 것을 없에는 함수
	CONSOLE_CURSOR_INFO cursorInfo; //cursorInfo를 선언
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) { //좌표를 지정해주는 함수
	COORD pos = { x, y };
	//x 는 가로 좌표값
	//y는 세로 좌표값
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}