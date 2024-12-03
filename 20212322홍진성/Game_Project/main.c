#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

#define WIDTH 62
#define HEIGHT 48
#define UX 30  //���� ������ x��ǥ
#define UY 45  //���� ������ y��ǥ
#define MAXBULLET 6
#define TRUE 1
#define FALSE 0

struct 
{
	int exist;
	int x, y;
}Bullet[MAXBULLET];

void textcolor(int Text_Color, int Background_Color);
void removeCursor(void);
void gotoxy(int x, int y);
void StartMenu(void);
void Help(void);
void Game_Start(void);
void Init_Game(void);
void playererase(int x, int y);
void palyerdraw();
int Delay = 10;
int Frame_Count = 0;
int P1_Frame_Sync = 4;
int called = 0;
int oldx = UX, oldy = UY; // �÷��̾��� old ��ǥ
int newx = UX, newy = UY; //�÷��̾��� new ��ǥ
int keep_moving = 1;  //1:����̵�
int x;
int y;
unsigned char ch;

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
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
	SPACEBAR = 32,
	SPECIAL1 = 0xE0, // 0xE0 �� �߰�
	SPECIAL2 = 0x00,  // 0x00 �� �߰�
	SPACE = 0x20, // 0X20 �� �߰�
};

void Help() {
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
			Game_Start();
			break;
		}
		else if (a == 2) { // Ű���� 2 �Է½� ���� ���
			Help();
		}
		else if (a == 3) { // Ű���� 3 �Է½� ���� ����
			printf("����");
			break;
		}
	}
}

void Game_Start() { //������ ���� ��Ű�� �Լ�
	unsigned char ch;

	int i;
	Init_Game(); //����۽� �ʱ�ȭ ���ִ� �Լ�
		while (1) {
			if (kbhit() == 1) {
				ch = getch();
				if (ch == SPECIAL1 || ch == SPECIAL2) {
					ch = getch();
					switch (ch) {
					case UP: case DOWN: case LEFT: case RIGHT: //Ű���带 �̿��Ͽ� �÷��̾� ��ġ ����
						Player_Move(ch);
						if (Frame_Count % P1_Frame_Sync == 0)
							Player_Move(0);
						break;
					default:
						if (Frame_Count % P1_Frame_Sync == 0)
							Player_Move(0);

					}
				}
				if (ch == SPACE) {
					for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) {}
					if (i != MAXBULLET) {
						Bullet[i].x = newx + 1;
						Bullet[i].y = newy - 1;
						Bullet[i].exist = TRUE;
					}
				}
			}
			
			else {
				//Player_Move �Լ� �ӵ� ����
			}
			Sleep(Delay); //Delay �� ���̱�
			Frame_Count++; //Frame_count ������ �ӵ� ����
		}
}

void Init_Game() {
	system("cls");
	removeCursor();
}

void playerdraw() {
	textcolr(GREEN, BLACK);
	gotoxy(x, y);
	printf("<<=��==>");
}

void DrawBullet(int i) {
	textcolor(GREEN, BLACK);
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf(" | ");
}

void EraseBullet(int i) {
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf("   ");
}

void Playr_Move() {
	int move_flag = 0;
	static unsigned char last_ch = 0;

	if (called == 0) {
		removeCursor();
		playerdraw(oldx, oldy);
		called = 1;
	}

	if (keep_moving && ch == 0)
		ch = last_ch;
	last_ch = ch;

	switch (ch) {
	case UP: // ����Ű ��Ű�� ������ ���� ��ġ�� ����
		if (oldy > 25)
			newy = oldy - 1;
		move_flag = 1;
		break;
	case DOWN: // ����Ű �Ʒ�Ű�� ������ �Ʒ��� ��ġ�� ����
		if (oldy < HEIGHT - 3)
			newy = oldy + 1;
		move_flag = 1;
		break;
	case LEFT: // ����Ű ����Ű�� ������ �������� ��ġ�� ����
		if (oldx > 2)
			newx = oldx - 1;
		move_flag = 1;
		break;
	case RIGHT: // ����Ű ������Ű�� ������ ���������� ��ġ�� ����
		if (oldx < WIDTH - 6)
			newx = oldx + 1;
		move_flag = 1;
		break;
	}
	if (move_flag) {
		playererase(oldx, oldy);
		playerdraw(newx, newy); 
		oldx = newx;
		oldy = newy;
	}
}

void playererase(int x, int y) {
	gotoxy(x, y);
	printf("   ");
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