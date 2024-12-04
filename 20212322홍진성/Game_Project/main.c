#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define _CRT_SECURE_NO_WARNINGS

#define WIDTH 62
#define HEIGHT 48
#define UX 30  //시작 유저의 x좌표
#define UY 45  //시작 유저의 y좌표

void textcolor(int Text_Color, int Background_Color);
void removeCursor(void);
void gotoxy(int x, int y);
void StartMenu(void);
void Help(void);
void Game_Start(void);
void Init_Game(void);
int Delay = 10;
int Frame_Count = 0;
int P1_Frame_Sync = 4;
int called = 0;
int oldx = UX, oldy = UY; // 플레이어의 old 좌표
int newx = UX, newy = UY; //플레이어의 new 좌표
int keep_moving = 1;  //1:계속이동

#define SPECIAL1 0XE0
#define SPECIAL2 0x00
#define SPACEBAR 0x20
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

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

enum Keys { //수업중에 사용한 키보드 함수를 복붙, 문제시 #define을 이용
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
	SPACEBAR = 32,
	SPECIAL1 = 0xE0, // 0xE0 값 추가
	SPECIAL2 = 0x00  // 0x00 값 추가
};

void Help() {
	system("cls"); //화면 지우기
	
	gotoxy(5, 10);
	printf("남자들에게는 가끔가슴이 울리는 조작법들이 있다...");

	gotoxy(15, 14);
	printf("절대 도움을 받아선 안돼... ");
	gotoxy(13, 18);
	printf("너의 가슴이 시키는대로 눌러라...\n\n\n\n");
	
	system("pause"); //help 종료	
}

void StartMenu() {
	int a;
	while (1) {
		system("cls");
		gotoxy(8, 2);
		printf("뿅뿅특공대!");
		gotoxy(8, 5);
		printf("게임시작(1)");
		gotoxy(9, 9);
		printf("도움말(2)");
		gotoxy(10, 13);
		printf("종료(3)");
		gotoxy(4, 17);
		printf("번호를 입력해주세요: ");
		scanf_s("%d", &a);

		if (a == 1) { //키보드 1 입력시 게임 시작
			Game_Start();
			break;
		}
		else if (a == 2) { // 키보드 2 입력시 도움말 출력
			Help();
		}
		else if (a == 3) { // 키보드 3 입력시 게임 종료
			printf("종료");
			break;
		}
	}
}

void Game_Start() { //게임을 시작 시키는 함수
	unsigned char ch;
	Init_Game(); //재시작시 초기화 해주는 함수
		while (1) {
			if (kbhit() == 1) {
				ch = getch();
				if (ch == SPECIAL1 || ch == SPECIAL2) {
					ch = getch();
					switch (ch) {
					case UP: case DOWN: case LEFT: case RIGHT: //키보드를 이용하여 플레이어 위치 변경
						Player_Move(ch);
						if (Frame_Count % P1_Frame_Sync == 0)
							Player_Move(0);
						break;
					default:
						if (Frame_Count % P1_Frame_Sync == 0)
							Player_Move(0);

					}
				}
			}
			else {

			}
			Sleep(Delay); //Delay 값 줄이기
			Frame_Count++; //Frame_count 값으로 속도 조절
		}
}

void Init_Game() {
	system("cls");
	removeCursor();
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
	case UP:
		if (oldy > 25)
			newy = oldy - 1;
		move_flag = 1;
		break;
	case DOWN:
		if (oldy < HEIGHT - 3)
			newy = oldy + 1;
		move_flag = 1;
		break;
	case LEFT:
		if (oldx > 2)
			newx = oldx - 1;
		move_flag = 1;
		break;
	case RIGHT:
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

int main() {
	srand(time(NULL)); //매번 같은 값을 출력
	textcolor(YELLOW, BLACK); //컬러 지정
	removeCursor(); //removeCursor 불러옴
	gotoxy(8, 20); //출력될 문장 좌표값 지정
	printf("뿅뿅특공대");
	StartMenu();
}