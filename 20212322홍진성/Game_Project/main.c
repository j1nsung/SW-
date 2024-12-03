#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void textcolor(int Text_Color, int Background_Color)
//Text_Color�� ������ ����
//Background_Color�� ����� ������ ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Text_Color | Background_Color << 4);
}

typedef enum Color { //���� �߿� ����� �÷� �Լ��� ����, ������ #define�� �̿� 
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
	textcolor(YELLOW, BLACK); //�÷� ����
}

void removeCursor(void) { //���콺 �����Ÿ��� ���� ������ �Լ�
	CONSOLE_CURSOR_INFO cursorInfo; //cursorInfo�� ����
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) { //��ǥ�� �������ִ� �Լ�
	COORD pos = { x, y };
	//x �� ���� ��ǥ��
	//y�� ���� ��ǥ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}