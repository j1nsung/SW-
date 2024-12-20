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
#define UX 10  //시작 유저의 x좌표
#define UY 15  //시작 유저의 y좌표
#define MAXBULLET 6
#define TRUE 1
#define FALSE 0
#define MAXENERMY 6
#define MAXENERMYBULLET 20

int Delay = 10;
int Frame_Count = 0;
int P1_Frame_Sync = 4;
int called = 0;
int oldx = UX , oldy = UY; // 플레이어의 old 좌표
int newx = UX, newy = UY; //플레이어의 new 좌표
int keep_moving = 1;  //1:계속이동
void Bullet_Move();
void Show_Enermy();
int Enermy_Bullet_Use = 1;
int Enermy_Bullet_frame_sync = 15;
void Enermy_Move();
void EnermyBullet_Show();
int score = 0;
int heart = 1;


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

struct 
{
	int exist;
	int x, y;
}Enermy_Bullet[MAXENERMYBULLET];

char* Enermy_Unit[] = { "⊙★⊙","＠▒＠","♨▣♨","◐▼◑" };

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

/*enum Keys { //수업중에 사용한 키보드 함수를 복붙, 문제시 #define을 이용
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
	SPACEBAR = 32,
	SPECIAL1 = 0xE0, // 0xE0 값 추가
	SPECIAL2 = 0x00  // 0x00 값 추가
};*/

void gotoxy(int x, int y) { //좌표를 지정해주는 함수
	COORD pos = { x, y };
	//x 는 가로 좌표값
	//y는 세로 좌표값
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



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

void removeCursor(void) { //마우스 깜빡거리는 것을 없에는 함수
	CONSOLE_CURSOR_INFO cursorInfo; //cursorInfo를 선언
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void playerdraw(int x, int y) {
		textcolor(GREEN, BLACK);
		gotoxy(x, y);
		printf("<=♥=>"); // 플레이어 출력
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
	case UP: // 방향키 윗키를 누르면 위로 위치값 변경
		if (oldy > 25) //화면 상단 제한
		{
			newy = oldy - 1;
			move_flag = 1;
		}
		break;
	case DOWN: // 방향키 아랫키를 누르면 아래로 위치값 변경
		if (oldy < HEIGHT - 3) //화면 하단 제한
		{
			newy = oldy + 1;
			move_flag = 1;
		}
		break;
	case LEFT: // 방향키 왼쪽키를 누르면 왼쪽으로 위치값 변경
		if (oldx > 2) //화면 좌측 제한
		{
			newx = oldx - 1;
			move_flag = 1;
		}
		break;
	case RIGHT: // 방향키 오른쪽키를 누르면 오른쪽으로 위치값 변경
		if (oldx < WIDTH - 6) //화면 우측 제한
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

void EnermyBullet_Show() {
	int j;
	int random = rand() % MAXENERMY;
	for (j = 0; j < MAXENERMYBULLET && Enermy_Bullet[j].exist == TRUE; j++) {}
	if (j != MAXENERMYBULLET && Enermy[random].exist == TRUE) {
		Enermy_Bullet[j].x = Enermy[random].x + 2;
		Enermy_Bullet[j].y = Enermy[random].y + 1;
		Enermy_Bullet[j].exist = TRUE;
	}
}

void EnermyBulletdraw(int i) {
	textcolor(RED, BLACK);
	gotoxy(Enermy_Bullet[i].x, Enermy_Bullet[i].y);
	printf("*");
}
void EnermyBulleterase(int i) {
	gotoxy(Enermy_Bullet[i].x, Enermy_Bullet[i].y);
	printf(" ");
}

void EnermyBulletMove() {
	int random;
	random = 1;
	for (int i = 0; i < MAXENERMYBULLET; i++) {
		if (Enermy_Bullet[i].exist == TRUE) {
			EnermyBulleterase(i);
			if (Enermy_Bullet[i].y > HEIGHT - 3) {
				Enermy_Bullet[i].exist = FALSE;
			}
			else {
				if (random) {
					if (Enermy_Bullet[i].x <= newx)
						Enermy_Bullet[i].x++;
					else
						Enermy_Bullet[i].x--;
				}
				Enermy_Bullet[i].y++;
				EnermyBulletdraw(i);
			}
		}
	}
}

void Enermy_fall() {
	int i;
	for (i = 0; i < MAXENERMY; i++) {
		if (Enermy[i].exist == FALSE || Enermy[i].type == -1)
			continue;
		if (Enermy[i].y == Bullet[i].y && abs(Enermy[i].x - Bullet[i].x) <= 7) {
			gotoxy(Bullet[i].x, Bullet[i].y);
			printf("   ");
			Bullet[i].exist = FALSE;
			Enermy[i].type = -1;
			score += 10;
			break;
		}
	}
}

void player_fall() {
	int i;
	for (i = 0; i < MAXENERMYBULLET; i++) {
		if (Enermy_Bullet[i].exist == FALSE)
			continue;
		if (Enermy_Bullet[i].y == newy && abs(Enermy_Bullet[i].x - newx) <= 3) {
			Enermy_Bullet[i].exist = FALSE;
			gotoxy(Enermy_Bullet[i].x, Enermy_Bullet[i].y);
			printf("    ");
			heart--;
		}
	}
}


void Game_Start() { //게임을 시작 시키는 함수
	unsigned char nKey;
	int i;

	Init_Game(); //재시작시 초기화 해주는 함수

	while (1) {
		if (_kbhit()) {
			nKey = _getch();
			if (nKey == SPECIAL1 || nKey == SPECIAL2) {
				nKey = _getch();
				switch (nKey) {
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT: //키보드를 이용하여 플레이어 위치 변경
					Player_Move(nKey);
					break;
				default:
					break;
				}
			}
			else if (nKey == SPACEBAR) { // 총알 발사
				for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) {}
				if (i != MAXBULLET) {
					Bullet[i].x = newx + 1;
					Bullet[i].y = newy - 1;
					Bullet[i].exist = TRUE;
				}
			}
		}
		if (Frame_Count % 50 == 0) { //50프레임마다 적 생성
			Show_Enermy();
		}

		Enermy_Move();

		if (Frame_Count % Enermy_Bullet_frame_sync == 0) {
			EnermyBullet_Show();
		}

		EnemyBulletMove();

		Bullet_Move(); //총알 이동
		Sleep(Delay); //Delay 값 줄이기
		Frame_Count++; //Frame_count 값으로 속도 조절
	}
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

void DrawBullet(int i) { //총알 생성하는 함수
	textcolor(GREEN, BLACK);
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf("|");
}

void EraseBullet(int i) { //총알이 생성된 자리를 다시 지우는 함수
	gotoxy(Bullet[i].x, Bullet[i].y);
	printf(" ");
}

void Bullet_Move() { //총알이 나가는 궤도를 y 좌표를 1 올리면서 진행
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

void Enermy_Move() { //적의 움직임을 나타내는 함수
	int i;
	for (i = 0; i < MAXENERMY; i++) {
		if (Enermy[i].exist == TRUE) {
			if (Enermy[i].type == -1) {
				gotoxy(Enermy[i].x - 1, Enermy[i].y);
				printf("          "); //적이 맞아 죽었을때 삭제하는 오브젝트
				Enermy[i].exist = FALSE; //위와 동일하게 죽었을 때 FALSE 값을 준다
				continue;
			}
			if (Enermy[i].x > 52) {
				Enermy[i].x -= 1;
				Enermy[i].move = -1;
			}
			else if (Enermy[i].x <= 3) {
				Enermy[i].move = 1;
				Enermy[i].x += 1;
				gotoxy(Enermy[i].x, Enermy[i].y);
				printf(" ");
			}
			else {
				Enermy[i].x += Enermy[i].move;
				gotoxy(Enermy[i].x, Enermy[i].y);
				printf(Enermy_Unit[Enermy[i].type]);
				printf(" ");
			}
		}
	}
}

int main() {
	srand(time(NULL)); //매번 같은 값을 출력
	textcolor(YELLOW, BLACK); //컬러 지정
	removeCursor(); //removeCursor 불러옴
	gotoxy(8, 20); //출력될 문장 좌표값 지정
	printf("뿅뿅특공대");
	StartMenu();
}