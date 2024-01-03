#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<mmsystem.h>;
#pragma comment(lib,"winmm.lib");


static int mode, level; //전역변수 level
int x = 0, y = 0;//gotoxy에 필요한 전역변수
int a[20][20] = { 0 }, row[20][20] = { 0 }, col[20][20] = { 0 }, customrow[20][20] = { 0 }, customcol[20][20] = { 0 }, userQcol[20][20] = { 0 }, userQrow[20][20] = { 0 };
//문제 배열들 Q
int easyQcol[20][20] = {
	{ 0,0,0,2,0, },
{ 0, 0, 1, 1, 0, },
{ 5,0,0,0,0, },
{ 0,0,1,1,0, },
{ 0,0,0,2,0, } };
int easyQrow[20][20] = {
	{ 0,0,0,1,5, },
{ 0,0,3,1,0 },
{ 1,1,0,1,0 },
{ 0,0,0,0,0 },
{ 0,0,0,0,0 }, };
int normalQcol[20][20] = {
	{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 2, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 7, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
int normalQrow[20][20] = {
	{ 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 6, 1, 6, 2, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 2, 0, 3, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 0, 0, 1, 0, 0, 0, 2, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

};
int hardQcol[20][20] = {
	{ 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 6, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 4, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 4, 2, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 0, 0, 1, 0, 0, 0, 2, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 0, 0, 2, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 2, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0 },
{ 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0 },
{ 1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 1, 0, 2, 0, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
{ 2, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 },
{ 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 0, 2, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 3, 2, 0, 0, 0, 0, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 5, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

};
int hardQrow[20][20] = {
	{ 20, 9, 7, 5, 3, 5, 2, 2, 2, 2, 2, 2, 2, 2, 5, 4, 6, 8, 9, 20 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0 },
{ 0, 9, 0, 0, 0, 0, 3, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 1, 8, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 2, 0, 0, 0, 8, 0, 2, 2, 0, 0, 0, 0, 0, 1, 7, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 6, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 6, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 3, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 4, 5, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 4, 2, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

void drawEasy();//정답공개(쉬움)
void drawNormal();//정답공개(보통)
void drawHard();//정답공개(어려움)
void title(); // 최초로 생성되는화면(타이틀)
void customGame(int level); // 커스텀 게임함수
void gotoxy(int x, int y); // 좌표값이동
void setCol(); // 아래에저장되어있는 퍼즐값
void setRow(); // 오른쪽에저장되어있는 퍼즐값
void fillLogic(int level); // 저장된퍼즐값을 그림으로 출력
void answer(); // 초기화한후 퍼즐값을 변환하는 함수
void playGame(int level); // 커스텀게임용 커서이동
void playGamecustom();//커스텀게임 좌표값이동 & 구현
void playGameforadventure();//어드벤쳐 게임 좌표값이동 & 구현
void adventure(int level);//어드벤쳐게임함수
void selectLevel();//레벨선택함수
void selectMode();//모드선택함수
void map(int level);//맵그려주는 함수
void customMap(int level);//커스텀맵그려주기
void run();//전체적인 실행함수
void problem(int level);//어드벤쳐용 문제 함수
void customProblem(int level);//커스텀용 문제 함수
void initRowcol();//Row col 초기화 함수
void initCustom();//커스텀배열 초기화함수
void saveCol();//커스텀 칼럼저장
void saveRow();//커스텀 로우저장
void initA();//전역배열 A 초기화함수
void answerAdventure();//어드벤쳐 정답확인 함수
void answerCustom();//커스텀 정답확인 함수

void initA() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			a[i][j] = 0;
		}
	}
}//A배열 초기화
void drawEasy() {
	for (int i = 0; i < 5; i++) {
		a[2][i] = 1;
		a[i][4] = 1;
	}
	a[1][2] = 1;
	a[3][2] = 1;
	a[0][3] = 1;
	a[4][3] = 1;
}////정답공개(쉬움)
void drawNormal() {
	a[0][1] = 1;
	a[9][1] = 1;
	a[8][6] = 1;
	a[6][7] = 1;
	a[8][7] = 1;
	a[9][7] = 1;
	for (int i = 0; i < 3; i++) {
		a[i][0] = 1;
		a[i + 7][0] = 1;
		a[i + 2][1] = 1;
		a[i + 5][1] = 1;
		a[i + 2][2] = 1;
		a[i + 5][2] = 1;
		a[i + 2][3] = 1;
		a[i + 5][3] = 1;
		a[i + 2][4] = 1;
		a[i + 5][4] = 1;
		a[i + 2][5] = 1;
		a[i + 5][5] = 1;
		a[i + 2][6] = 1;
		a[i + 5][6] = 1;
		a[i + 3][7] = 1;
		a[i + 4][8] = 1;
		a[i + 7][8] = 1;
		a[i + 4][9] = 1;
		a[i + 7][9] = 1;

	}
	a[3][3] = 0;
	a[6][3] = 0;
	a[4][5] = 0;
	a[5][8] = 0;
	a[6][8] = 0;
}//정답공개(보통)
void drawHard() {
	for (int j = 0; j < 20; j++) {
		for (int i = 0; i < 20; i++) {
			a[i][j] = 1;
		}
	}//색칠

	for (int i = 0; i < 2; i++) {
		a[i + 9][1] = 0;
		a[i + 2][6] = 0;
		a[i + 16][6] = 0;
		a[i + 8][9] = 0;
		a[i + 8][10] = 0;
		a[i + 2][11] = 0;
		a[i + 2][12] = 0;
		a[i + 8][17] = 0;
		a[i + 11][16] = 0;
		a[i + 11][17] = 0;
	}//공백변환2

	for (int i = 0; i < 4; i++) {
		a[i + 5][3] = 0;
		a[i + 2][7] = 0;
		a[i + 14][7] = 0;
		a[i + 2][8] = 0;
		a[i + 6][8] = 0;
		a[i + 2][9] = 0;
		a[i + 2][10] = 0;
		a[i + 6][11] = 0;
		a[i + 6][12] = 0;
		a[i + 6][16] = 0;
		a[i + 14][9] = 0;
		a[i + 14][10] = 0;
		a[i + 11][11] = 0;
		a[i + 11][12] = 0;
		a[i + 11][15] = 0;
	}//공백변환4

	for (int i = 0; i < 5; i++) {
		a[i + 11][4] = 0;
		a[i + 5][5] = 0;
		a[i + 10][5] = 0;
		a[i + 5][13] = 0;
		a[i + 5][14] = 0;
		a[i + 5][14] = 0;
		a[i + 11][14] = 0;
	}//공백변환5

	for (int i = 0; i < 6; i++) {
		a[i + 7][2] = 0;
		a[i + 11][3] = 0;
		a[i + 3][4] = 0;
		a[i + 7][6] = 0;
		a[i + 11][8] = 0;
		a[i + 4][15] = 0;
		a[i + 11][13] = 0;

	}//공백변환6

	a[13][2] = 0;
	a[17][5] = 0;
	a[17][8] = 0;
	a[2][13] = 0;
	a[9][18] = 0;
	a[13][16] = 0;
	a[11][18] = 0;
	a[11][9] = 0;
	a[11][10] = 0;
	a[17][11] = 0;
	a[17][12] = 0;
}//정답공개(어려움)
void fillLogic(int level) {
	if (level == 1) {
		level = 5;
	}
	else if (level == 2) {
		level = 10;
	}
	else if (level == 3) {
		level = 20;
	}
	x = 0, y = 0;
	gotoxy(x, y);
	for (int j = 0; j < level; j++) {
		for (int i = 0; i < level; i++) {
			gotoxy(j * 2, i);
			if (a[j][i] == 1)
				printf("■");
			else if ((a[j][i] == 0) || (a[j][i] == 3)) {
				printf("□");
			}
		}
	}
}//정답공개함수
void answer() {
	//test 오른쪽  아래 칼럼, 로우 표시만 지우기
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			gotoxy(40 + 2 * j, i);
			printf("                                 ");
			gotoxy(2 * j, 20 + i);
			printf("  ");
		}
	}
	//row,col 배열 초기화
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			row[i][j] = 0;
			col[i][j] = 0;
		}
	}
	setRow();
	setCol();
}//초기화한후 퍼즐값을 변환하는 함수
void setRow() {
	int count = 0, temp = 0;;//연속으로 1이면 count++ , col변수 중복으로 덮어씌우지 않게

	for (int i = 0; i < 20; i++) {
		count = 0;
		for (int j = 0; j < 20; j++) {
			//마지막 칸일때
			if (j == 19) {
				if (a[j][i] == 1) {
					count++;
					row[temp][i] = count;
				}
				else
					row[temp][i] = count;
			}
			else if (a[j][i] == 1) {
				count++;
			}
			else {
				row[temp][i] = count;
				temp++;
				count = 0;
			}
		}
		temp = 0;
	}
	//row 행렬 출력
	if (level == 20 && mode == 2) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (row[j][i] != 0) {
					gotoxy(62 + (3 * temp), i);
					printf("%d ", row[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
	}
	else if (level == 20 && mode == 1) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (row[j][i] != 0) {
					gotoxy(82 + (3 * temp), i);
					printf("%d ", row[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
	}
	else {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (row[j][i] != 0) {
					gotoxy(42 + (3 * temp), i);
					printf("%d ", row[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
	}
} // 오른쪽에저장되어있는 퍼즐값
void setCol() {
	int count = 0, temp = 0;;//연속으로 1이면 count , row변수 중복으로 덮어씌우지 않게
	for (int i = 0; i < 20; i++) {
		count = 0;
		for (int j = 0; j < 20; j++) {
			//마지막 칸일때
			if (j == 19) {
				if (a[i][j] == 1) {
					count++;
					col[i][temp] = count;
				}
				else
					col[i][temp] = count;
			}
			else if (a[i][j] == 1) {
				count++;
			}
			else {
				col[i][temp] = count;
				temp++;
				count = 0;
			}
		}
		temp = 0;
	}
	//col 출력
	if (level == 20) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (col[i][j] != 0) {
					gotoxy(i * 2, 27 + temp);
					printf("%2d", col[i][j]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
	}
	else {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (col[i][j] != 0) {
					gotoxy(i * 2, 21 + temp);
					printf("%2d", col[i][j]);
					temp++;
				}
			}
			temp = 0;
		}
	}
}// 아래에저장되어있는 퍼즐값
void initRowcol() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			row[i][j] = 0;
			col[i][j] = 0;
			a[i][j] = 0;
		}
	}
}//Row col 초기화 함수
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}//gotoxy함수 좌표값이동
void customGame(int level) {
	customMap(level);
	playGame(level);
}//커스텀게임실행함수
void adventure(int level) {
	system("cls");
	initRowcol();
	map(level);
	playGameforadventure();
}//어드벤쳐게임실행함수
void map(int level) {
	system("cls");
	if (level == 1) {
		level = 5;
	}
	else if (level == 2) {
		level = 10;
	}
	else if (level == 3) {
		level = 20;
	}
	int i, j;
	x = 0, y = 0;
	gotoxy(x, y);
	for (j = 0; j < level; j++) {
		for (i = 0; i < level; i++) {
			printf("□");
		}
		y++;
		gotoxy(x, y);
	}
	gotoxy(60, 20);
	printf("네모네모로직 ver 1.0");
	gotoxy(60, 22);
	printf("[a를 누르면 정답을 제출합니다.]");
	gotoxy(60, 24);
	printf("[r을 누르면 게임을 포기합니다.]");
	gotoxy(60, 26);
	printf("[x를 누르면 깃발을 세울 수 있습니다.]");
	gotoxy(60, 28);
	if (level == 5) {
		printf("[Easy Mode]");
	}
	else if (level == 10) {
		printf("[Normal Mode]");
	}
	else if (level == 20) {
		printf("[Hard Mode]");
	}

}//네모네모로직 맵 구현 함수
void customMap(int level) {
	system("cls");
	if (level == 1) {
		level = 5;
	}
	else if (level == 2) {
		level = 10;
	}
	else if (level == 3) {
		level = 20;
	}
	int i, j;
	x = 0, y = 0;
	gotoxy(x, y);
	for (j = 0; j < level; j++) {
		for (i = 0; i < level; i++) {
			printf("□");
		}
		y++;
		gotoxy(x, y);
	}
	gotoxy(60, 20);
	printf("네모네모로직 ver 1.0");
	gotoxy(60, 22);
	printf("[a를 누르면 정답을 제출합니다.]");
	gotoxy(60, 24);
	printf("[r을 누르면 게임을 포기합니다.]");
	gotoxy(60, 26);
	printf("[x를 누르면 깃발을 세울 수 있습니다.]");
	gotoxy(60, 28);
	printf("[z를 누르면 문제화 시킬 수 있습니다.]");
	gotoxy(60, 30);
	if (level == 5) {
		printf("[Easy Mode]");
	}
	else if (level == 10) {
		printf("[Normal Mode]");
	}
	else if (level == 20) {
		printf("[Hard Mode]");
	}

}//커스텀용 네모로직 맵 구현함수
void playGame(int level) {
	char curser;
	if (level == 1) {
		level = 5;
	}
	else if (level == 2) {
		level = 10;
	}
	else if (level == 3) {
		level = 20;
	}
	while (1) {
		curser = _getch();
		switch (curser) {
		case 72:
			if ((y - 1) != (-1))
				y -= 1;
			break;
		case 75:
			if ((x - 1) != (-1))
				x -= 1;
			break;
		case 80:
			if ((y + 1) != level)
				y += 1;
			break;
		case 77:
			if ((x + 1) != level)
				x += 1;
			break;
		case 32:
			if ((a[x][y] == 0) || (a[x][y] == 3)) {
				printf("■");
				a[x][y] = 1;
			}
			else if (a[x][y] == 1) {
				printf("□");
				a[x][y] = 0;
			}
			break;
		case 'x':
			if ((a[x][y] == 0) || (a[x][y] == 1)) {
				printf("▨");
				a[x][y] = 3;
			}
			else if (a[x][y] == 3) {
				printf("□");
				a[x][y] = 0;
			}
			break;

		case 'a':
			answer();
			break;

		case 'r':
			initRowcol();
			run();
			break;

		case 'z':
			saveCol();
			saveRow();
			map(level);
			initA();
			customProblem(level);
			playGamecustom();
			_getch();
			break;
		}
		gotoxy(x * 2, y);
	}
}//게임구동함수 커스텀용
void problem(int level) {
	int temp = 0;
	if (level == 5) {
		//오른쪽easy 문제 출력row
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (easyQrow[j][i] != 0) {
					gotoxy(12 + (3 * temp), i);
					printf("%d ", easyQrow[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
		//아래 easy 문제 출력 col
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (easyQcol[i][j] != 0) {
					gotoxy(i * 2, 6 + temp);
					printf("%2d", easyQcol[i][j]);
					temp++;
				}
			}
			temp = 0;
		}
	}
	else if (level == 10) {
		//오른쪽easy 문제 출력row
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (normalQrow[j][i] != 0) {
					gotoxy(22 + (3 * temp), i);
					printf("%d ", normalQrow[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
		//아래 easy 문제 출력 col
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (normalQcol[i][j] != 0) {
					gotoxy(i * 2, 11 + temp);
					printf("%2d", normalQcol[i][j]);
					temp++;
				}
			}
			temp = 0;
		}
	}
	else if (level == 20) {
		//오른쪽easy 문제 출력row
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (hardQrow[j][i] != 0) {
					gotoxy(42 + (3 * temp), i);
					printf("%d ", hardQrow[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
		//아래 easy 문제 출력 col
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (hardQcol[i][j] != 0) {
					gotoxy(i * 2, 21 + temp);
					printf("%2d", hardQcol[i][j]);
					temp++;
				}
			}
			temp = 0;
		}
	}
}//문제 출력 함수
void customProblem(int level) {
	int temp = 0;
	if (level == 5) {
		//오른쪽easy 문제 출력row
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (customrow[j][i] != 0) {
					gotoxy(12 + (3 * temp), i);
					printf("%d ", customrow[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
		//아래 easy 문제 출력 col
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (customcol[i][j] != 0) {
					gotoxy(i * 2, 6 + temp);
					printf("%2d", customcol[i][j]);
					temp++;
				}
			}
			temp = 0;
		}
	}
	else if (level == 10) {
		//오른쪽easy 문제 출력row
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (customrow[j][i] != 0) {
					gotoxy(22 + (3 * temp), i);
					printf("%d ", customrow[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
		//아래 easy 문제 출력 col
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (customcol[i][j] != 0) {
					gotoxy(i * 2, 11 + temp);
					printf("%2d", customcol[i][j]);
					temp++;
				}
			}
			temp = 0;
		}
	}
	else if (level == 20) {
		//오른쪽easy 문제 출력row
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (customrow[j][i] != 0) {
					gotoxy(42 + (3 * temp), i);
					printf("%d ", customrow[j][i]);
					temp++;
				}
			}
			temp = 0;
			printf("\n");
		}
		//아래 easy 문제 출력 col
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if (customcol[i][j] != 0) {
					gotoxy(i * 2, 21 + temp);
					printf("%2d", customcol[i][j]);
					temp++;
				}
			}
			temp = 0;
		}
	}
}//커스텀용 문제 출력함수
void playGameforadventure() {
	int temp = 0;
	if (level == 1) {
		level = 5;
	}
	else if (level == 2) {
		level = 10;
	}
	else if (level == 3) {
		level = 20;
	}
	problem(level);

	char curser;
	while (1) {
		curser = _getch();
		switch (curser) {
		case 72:
			if ((y - 1) != (-1))
				y -= 1;
			break;
		case 75:
			if ((x - 1) != (-1))
				x -= 1;
			break;
		case 80:
			if ((y + 1) != level)
				y += 1;
			break;
		case 77:
			if ((x + 1) != level)
				x += 1;
			break;
		case 32:
			if ((a[x][y] == 0) || (a[x][y] == 3)) {
				printf("■");
				a[x][y] = 1;
			}
			else if (a[x][y] == 1) {
				printf("□");
				a[x][y] = 0;
			}
			break;
		case 'x':
			if ((a[x][y] == 0) || (a[x][y] == 1)) {
				printf("▨");
				a[x][y] = 3;
			}
			else if (a[x][y] == 3) {
				printf("□");
				a[x][y] = 0;
			}
			break;

		case 'a':
			answer();
			answerAdventure();
			problem(level);
			break;

		case 'r':
			initA();
			if (level == 5) {
				drawEasy();
			}
			else if (level == 10) {
				drawNormal();
			}
			else if (level == 20) {
				drawHard();
			}

			fillLogic(level);
			Sleep(3000);
			initA();
			run();
			break;



		}
		gotoxy(x * 2, y);
	}
}//어드벤쳐용 게임 구현 함수
void answerAdventure() {
	int judgeans = 0;//정답인지 확인하는 함수.
	if (level == 5) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if ((row[i][j] != easyQrow[i][j]) || (col[i][j] != easyQcol[i][j])) {
					gotoxy(48, 24);
					printf("[X]");
					gotoxy(43, 25);
					printf("정답이 아닙니다.");
					judgeans++;
				}
			}
		}
	}

	if (level == 10) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if ((row[i][j] != normalQrow[i][j]) || (col[i][j] != normalQcol[i][j])) {
					gotoxy(48, 24);
					printf("[X]");
					gotoxy(43, 25);
					printf("정답이 아닙니다.");
					judgeans++;
				}
			}
		}
	}

	if (level == 20) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				if ((row[i][j] != hardQrow[i][j]) || (col[i][j] != hardQcol[i][j])) {
					gotoxy(48, 24);
					printf("[X]");
					gotoxy(43, 25);
					printf("정답이 아닙니다.");
					judgeans++;
				}
			}
		}
	}

	if (judgeans == 0) {
		gotoxy(48, 24);
		printf("[O]");
		gotoxy(43, 25);
		printf(" 정답 입니다.   ");
	}
}
void playGamecustom() {
	int temp = 0;
	if (level == 1) {
		level = 5;
	}
	else if (level == 2) {
		level = 10;
	}
	else if (level == 3) {
		level = 20;
	}
	customProblem(level);

	char curser;
	while (1) {
		curser = _getch();
		switch (curser) {
		case 72:
			if ((y - 1) != (-1))
				y -= 1;
			break;
		case 75:
			if ((x - 1) != (-1))
				x -= 1;
			break;
		case 80:
			if ((y + 1) != level)
				y += 1;
			break;
		case 77:
			if ((x + 1) != level)
				x += 1;
			break;
		case 32:
			if ((a[x][y] == 0) || (a[x][y] == 3)) {
				printf("■");
				a[x][y] = 1;
			}
			else if (a[x][y] == 1) {
				printf("□");
				a[x][y] = 0;
			}
			break;
		case 'x':
			if ((a[x][y] == 0) || (a[x][y] == 1)) {
				printf("▨");
				a[x][y] = 3;
			}
			else if (a[x][y] == 3) {
				printf("□");
				a[x][y] = 0;
			}
			break;

		case 'a':
			answer();
			answerCustom();
			customProblem(level);
			break;

		case 'r':
			initCustom();
			run();
			break;

		}
		gotoxy(x * 2, y);
	}
}//커스텀용 게임 구현 함수
void answerCustom() {
	int judgeans = 0;//정답인지 확인하는 함수.
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if ((row[i][j] != customrow[i][j]) || (col[i][j] != customcol[i][j])) {
				gotoxy(48, 24);
				printf("[X]");
				gotoxy(43, 25);
				printf("정답이 아닙니다.");
				judgeans++;
			}
		}
	}

	if (judgeans == 0) {
		gotoxy(48, 24);
		printf("[O]");
		gotoxy(43, 25);
		printf(" 정답 입니다.   ");
	}
}
void selectLevel() {
	system("cls");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("　　　　　난이도를 선택해주세요.\n　　　　　1: 5 X 5    2: 10 X 10    3: 20 X 20 >>");
	scanf_s("%d", &level);
}//레벨선택함수
void title() {
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("　　　　　□　　　　　□　□　　□□□□□　　□□□□□　□□□□□　□　\n");
	printf("　　　　　□　　　　　□　□　　□　　　□　　　　　□□　　　□　　　□　\n");
	printf("　　　　　□　　　　　□　□　　□□□□□　　　□□□　　　□  □　　□　\n");
	printf("　　　　　□　　□□□□　□　　　　□　　　　□□□□□　　　　　　　□　\n");
	printf("　　　　　□　　　　　□　□　　　　□　　　　　　□　　　□□□□□□□　\n");
	printf("　　　　　□□□□　　□  □　　□□□□□　　□□□□□　　　　　　　□　\n");
	printf("\n");
	printf("　　　　　　　　　　　　　　계속하려면 아무키나 누르십시오.　　　　　　　　　\n");
	_getch();
}//타이틀 출력 함수
void selectMode() {

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("　　　　　모드를 선택하세요\n　　　　　1:Custom    2:Adventure >> ");
	scanf_s("%d", &mode);
}//모드 선택 함수
void run() {
	system("cls");
	selectMode();
	selectLevel();
	if ((mode == 1) && (level>=1) && (level <= 3)  ) {
		customGame(level);
	}
	else if ((mode == 2) && (level >= 1) && (level <= 3)) {
		adventure(level);
	}
	else {
		exit(1);
	}
} //전체적인 싫행함수(메인함수에서 실행됨)
void saveCol() {
	int count, temp = 0;//연속으로 1이면 count ,row변수 중복으로 덮어씌우지 않게
	for (int i = 0; i < 20; i++) {
		count = 0;
		for (int j = 0; j < 20; j++) {
			//마지막 칸일때
			if (j == 19) {
				if (a[i][j] == 1) {
					count++;
					customcol[i][temp] = count;
				}
				else
					customcol[i][temp] = count;
			}
			else if (a[i][j] == 1) {
				count++;
			}
			else {
				customcol[i][temp] = count;
				temp++;
				count = 0;
			}
		}
		temp = 0;
	}
}//열저장하는 함수(커스텀용)
void saveRow() {
	int count, temp = 0;//연속으로 1이면 count++ , col변수 중복으로 덮어씌우지 않게
	for (int i = 0; i < 20; i++) {
		count = 0;
		for (int j = 0; j < 20; j++) {
			//마지막 칸일때
			if (j == 19) {
				if (a[j][i] == 1) {
					count++;
					customrow[temp][i] = count;
				}
				else
					customrow[temp][i] = count;
			}
			else if (a[j][i] == 1) {
				count++;
			}
			else {
				customrow[temp][i] = count;
				temp++;
				count = 0;
			}
		}
		temp = 0;
	}
}//행저장하는 함수(커스텀용)
void initCustom() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			customrow[i][j] = 0;
			customcol[i][j] = 0;
			a[i][j] = 0;
		}
	}
}//커스텀용 배열 초기화 함수
int main() {
	PlaySound(TEXT("C:\\Users\\user\\Downloads\\bgm.wav"), NULL, SND_ASYNC | SND_LOOP);
	title();
	run();
	system("pause");
	return 0;
}//메인함수
