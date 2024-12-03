#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void textcolor(int Text_Color, int Background_Color);
void removeCursor(void);
void gotoxy(int x, int y);
void StartMenu(void);
void help(void);

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

enum Keys { //�����߿� ����� Ű���� �Լ��� ����, ������ #define�� �̿�
	LEFT = 75,
	Right = 77,
	UP = 72,
	DOWN = 80,
	ARROW = 224,
	SPACEBAR = 32
};

void help() {
	system("cls"); //ȭ�� �����
	
	gotoxy(5, 10);
	printf("���ڵ鿡�Դ� ���������� �︮�� ���۹����� �ִ�...");

	gotoxy(15, 14);
	printf("���� ������ �޾Ƽ� �ȵ�... ");
	gotoxy(13, 18);
	printf("���� ������ ��Ű�´�� ������...\n\n\n\n");
	
	system("pause"); //help ����	
}

void StartMenu() {
	int a;
	while (1) {
		system("cls");
		gotoxy(8, 2);
		printf("�л�Ư����!");
		gotoxy(8, 5);
		printf("���ӽ���(1)");
		gotoxy(9, 9);
		printf("����(2)");
		gotoxy(10, 13);
		printf("����(3)");
		gotoxy(4, 17);
		printf("��ȣ�� �Է����ּ���: ");
		scanf_s("%d", &a);

		if (a == 1) { //Ű���� 1 �Է½� ���� ����
			//gamestart();
			break;
		}
		else if (a == 2) { // Ű���� 2 �Է½� ���� ���
			help();
		}
		else if (a == 3) { // Ű���� 3 �Է½� ���� ����
			printf("����");
			break;
		}
	}
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

int main() {
	srand(time(NULL)); //�Ź� ���� ���� ���
	textcolor(YELLOW, BLACK); //�÷� ����
	removeCursor(); //removeCursor �ҷ���
	gotoxy(8, 20); //��µ� ���� ��ǥ�� ����
	printf("�л�Ư����");
	StartMenu();
}