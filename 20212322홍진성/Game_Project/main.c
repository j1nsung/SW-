#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS



#define SPECIAL1 0XE0
#define SPECIAL2 0x00
#define SPACEBAR 0x20
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d




#define WIDTH 40
#define HEIGHT 30
#define UX 10  //���� ������ x��ǥ
#define UY 15  //���� ������ y��ǥ
#define MAXBULLET 6
#define TRUE 1
#define FALSE 0
#define MAXENERMY 6

int Delay = 10;
int Frame_Count = 0;
int P1_Frame_Sync = 4;
int called = 0;
int oldx = UX , oldy = UY; // �÷��̾��� old ��ǥ
int newx = UX, newy = UY; //�÷��̾��� new ��ǥ
int keep_moving = 1;  //1:����̵�
void Bullet_Move();

struct
{
	int exist;
	int x, y;
}Bullet[MAXBULLET];

struct
{
	int exist;
	int x, y;
	int number;
	int move;
	int type;
}Enermy[MAXENERMY];

char* Enermy_Unit[] = { "���ڢ�","���ƣ�","�͢â�","�ġ��" };

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

/*enum Keys { //�����߿� ����� Ű���� �Լ��� ����, ������ #define�� �̿�
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
	SPACEBAR = 32,
	SPECIAL1 = 0xE0, // 0xE0 �� �߰�
	SPECIAL2 = 0x00  // 0x00 �� �߰�
};*/

void gotoxy(int x, int y) { //��ǥ�� �������ִ� �Լ�
	COORD pos = { x, y };
	//x �� ���� ��ǥ��
	//y�� ���� ��ǥ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



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

void removeCursor(void) { //���콺 �����Ÿ��� ���� ������ �Լ�
	CONSOLE_CURSOR_INFO cursorInfo; //cursorInfo�� ����
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void playerdraw(int x, int y) {
		textcolor(GREEN, BLACK);
		gotoxy(x, y);
		printf("<=��=>"); // �÷��̾� ���
}



void Init_Game() {
	system("cls");
	removeCursor();
	playerdraw(oldx, oldy);
}


void playererase(int x, int y) {
	gotoxy(x, y);
	printf("      ");
	fflush(stdout);
}

void Player_Move(unsigned char nKey) {
	int move_flag = 0;

	switch (nKey) 
	{
	case UP: // ����Ű ��Ű�� ������ ���� ��ġ�� ����
		if (oldy > 25) //ȭ�� ��� ����
		{
			newy = oldy - 1;
			move_flag = 1;
		}
		break;
	case DOWN: // ����Ű �Ʒ�Ű�� ������ �Ʒ��� ��ġ�� ����
		if (oldy < HEIGHT - 3) //ȭ�� �ϴ� ����
		{
			newy = oldy + 1;
			move_flag = 1;
		}
		break;
	case LEFT: // ����Ű ����Ű�� ������ �������� ��ġ�� ����
		if (oldx > 2) //ȭ�� ���� ����
		{
			newx = oldx - 1;
			move_flag = 1;
		}
		break;
	case RIGHT: // ����Ű ������Ű�� ������ ���������� ��ġ�� ����
		if (oldx < WIDTH - 6) //ȭ�� ���� ����
		{
			newx = oldx + 1;
			move_flag = 1;
		}
		break;
	default:
		break;
	}
	if (move_flag) {
		playererase(oldx, oldy);
		playerdraw(newx, newy);
		oldx = newx;
		oldy = newy;
	}
}

void Game_Start() { //������ ���� ��Ű�� �Լ�
	unsigned char nKey;
	int i;

	Init_Game(); //����۽� �ʱ�ȭ ���ִ� �Լ�

	while (1) {
		if (_kbhit()) {
			nKey = _getch();
			if (nKey == SPECIAL1 || nKey == SPECIAL2) {
				nKey = _getch();
				switch (nKey) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT: //Ű���带 �̿��Ͽ� �÷��̾� ��ġ ����
					Player_Move(nKey);
					break;
				default:
					break;
				}
			}
			else if (nKey == SPACEBAR) { // �Ѿ� �߻�
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
		Bullet_Move(); //�Ѿ� �̵�
		Sleep(Delay); //Delay �� ���̱�
		Frame_Count++; //Frame_count ������ �ӵ� ����
	}
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

void DrawBullet(int i) {
	textcolor(GREEN, BLACK);
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf("|");
}

void EraseBullet(int i) {
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf(" ");
}

void Bullet_Move() {
	int i;

	for (i = 0; i < MAXBULLET; i++) {
		if (Bullet[i].exist == TRUE) {
			EraseBullet(i);
			if (Bullet[i].y == 0) {
				Bullet[i].exist = FALSE;
			}
			else 
			{
				Bullet[i].y--;
				DrawBullet(i);
			}
		}
	}	
}

void Show_Enermy() {
	int i, location, direct, height;
	location = rand() % 2;
	direct = 5 + rand() % 55;
	height = 1 + rand() % 8;
	for(i=0; i < MAXENERMY && Enermy[i].exist==TRUE; i++){}
	if (i != MAXENERMY) {
		if (location == 1) {
			Enermy[i].x = direct;
			Enermy[i].y = height;
			Enermy[i].move = 1;
		}
		else {
			Enermy[i].x = direct;
			Enermy[i].y = height;
			Enermy[i].move = -1;
		}
		Enermy[i].type = rand() % 4;
		Enermy[i].exist = TRUE;	
	}
}

int main() {
	srand(time(NULL)); //�Ź� ���� ���� ���
	textcolor(YELLOW, BLACK); //�÷� ����
	removeCursor(); //removeCursor �ҷ���
	gotoxy(8, 20); //��µ� ���� ��ǥ�� ����
	printf("�л�Ư����");
	StartMenu();
}