#include "ScoreBoard.h"

//ghostHunter

string name;
int sc = 0; //score
int lp = 3; //LP
int pt = 30;//count point
int pHunter = 0;//power hunter
int countPower = 2;//count power
int countWalk = 0;//count walk
int randomMap;//randommap
int timePower = 0;//time of power

struct ghost {
	int gx;
	int gy;
}ghost[18];

struct hunter {
	int x;
	int y;
}hunter;

struct point {
	int px;
	int py;
}point[30];

struct power {
	int powx;
	int powy;
}POW[2];

void main_menu() {//main menu
	gotoxy(0, 0);
	setcolor(7, 0);
	FILE* fp;
	fp = fopen("main_menu.txt", "r");
	while (!feof(fp)) {
		char c = fgetc(fp);
		printf("%c", c);
	}
	fclose(fp);
	setcolor(6, 0);
	gotoxy(16, 16);
	printf("press any key to continue"); 
	setcolor(4, 0);
	gotoxy(18, 19);
	printf("press x to quit game");
	setcolor(2, 0);
	gotoxy(17, 22);
	printf("press s to score board");
}

void player_name() {//Enter player name
	gotoxy(0, 0);
	setcolor(7, 0);
	FILE* fp;
	fp = fopen("player_name.txt", "r");
	while (!feof(fp)) {
		char c = fgetc(fp);
		printf("%c", c);
	}
	fclose(fp);
	setcolor(6, 0);
	gotoxy(16, 21);
	printf("press enter to continue");
	gotoxy(27, 17);
	setcolor(7, 0);
	cin >> name;
}

void exit_menu() {
	gotoxy(0, 0);
	setcolor(7, 0);
	FILE* fp;
	fp = fopen("exit_menu.txt", "r");
	while (!feof(fp)) {
		char c = fgetc(fp);
		printf("%c", c);
	}
	fclose(fp);
	
}

void draw_map1() {//map1
	gotoxy(0, 0);
	setcolor(7, 0);
	FILE* fp;
	fp = fopen("map1.txt", "r");
	while (!feof(fp)) {
		char c = fgetc(fp);
		printf("%c", c);
	}
	fclose(fp);
}

void draw_map2() {
	gotoxy(0, 0);
	setcolor(7, 0);
	FILE* fp;
	fp = fopen("map2.txt", "r");
	while (!feof(fp)) {
		char c = fgetc(fp);
		printf("%c", c);
	}
	fclose(fp);
}

void game_over() {//clear screen
	ScoreBoard(name, sc);
	gotoxy(0, 0);
	setcolor(7, 0);
	FILE* fp;
	fp = fopen("game_over.txt", "r");
	while (!feof(fp)) {
		char c = fgetc(fp);
		printf("%c", c);
	}
	fclose(fp);
	gotoxy(31,23);
	cout << sc;
	_getch(); //keyboard check
}

void score_board() {
	gotoxy(0, 0);
	setcolor(7, 0);
	scoreUI();
}

void draw_hunter(int x, int y) {//draw hunter
	gotoxy(x, y);
	setcolor(6, 0);
	printf("O");
}

void del_draw(int x, int y) {//delete draw
	gotoxy(x, y);
	printf(" ");
}

void setcursor(bool visible) {//ON-OFF cursor
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y };
	DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read)) {
		return 0;
	}
	else {
		return buf[0];
	}
}

void draw_ghost(int x, int y) {//draw ghost
	gotoxy(x, y);
	setcolor(4, 0);
	printf("W");
}

void draw_superGhost(int x, int y) {//draw super ghost
	gotoxy(x, y);
	setcolor(5, 0);
	printf("W");
}

void draw_point() {//draw point
	for (int i = 0; i <= 29; i++) {
		gotoxy(point[i].px, point[i].py);
		setcolor(3, 0);
		printf(".");
	}
}

void draw_power(int i) {//draw power
	gotoxy(POW[i].powx, POW[i].powy);
	setcolor(2, 0);
	printf("P");
}

void ghost_run() {
	int i;
	for (int a = 4; a <= 17; a++) {
		i = rand() % 4 + 1;
		if (i == 1) {
			if (cursor(ghost[a].gx - 1, ghost[a].gy) == 'x' || (ghost[a].gx == 1)) {
				draw_ghost(ghost[a].gx, ghost[a].gy);
			}
			else {
				del_draw(ghost[a].gx, ghost[a].gy);
				draw_ghost(--ghost[a].gx, ghost[a].gy);
			}
		}
		if (i == 2) {
			if (cursor(ghost[a].gx + 1, ghost[a].gy) == 'x' || (ghost[a].gx == 50)) {
				draw_ghost(ghost[a].gx, ghost[a].gy);
			}
			else {
				del_draw(ghost[a].gx, ghost[a].gy);
				draw_ghost(++ghost[a].gx, ghost[a].gy);
			}
		}
		if (i == 3) {
			if (cursor(ghost[a].gx, ghost[a].gy - 1) == 'x' || (ghost[a].gy == 1)) { //if hunter hit the wall then continue
				draw_ghost(ghost[a].gx, ghost[a].gy);
			}
			else {
				del_draw(ghost[a].gx, ghost[a].gy);
				draw_ghost(ghost[a].gx, --ghost[a].gy);
			}
		}
		if (i == 4) {
			if (cursor(ghost[a].gx, ghost[a].gy + 1) == 'x' || (ghost[a].gy == 25)) {
				draw_ghost(ghost[a].gx, ghost[a].gy);
			}
			else {
				del_draw(ghost[a].gx, ghost[a].gy);
				draw_ghost(ghost[a].gx, ++ghost[a].gy);
			}
		}
		for (int b = 0; b <= 29; b++) { //if ghost hit point then nothing happen
			if ((ghost[a].gy - 1 == point[b].py && ghost[a].gx == point[b].px) || (ghost[a].gx - 1 == point[b].px && ghost[a].gy == point[b].py) ||
				(ghost[a].gx + 1 == point[b].px && ghost[a].gy == point[b].py) || (ghost[a].gy + 1 == point[b].py && ghost[a].gx == point[b].px)) {
				gotoxy(point[b].px, point[b].py);
				setcolor(3, 0);
				printf(".");
			}
		}
		for (int b = 0; b <= 1; b++) { //if ghost hit power then nothing happen
			if ((ghost[a].gy - 1 == POW[b].powy && ghost[a].gx == POW[b].powx) || (ghost[a].gx - 1 == POW[b].powx && ghost[a].gy == POW[b].powy) ||
				(ghost[a].gx + 1 == POW[b].powx && ghost[a].gy == POW[b].powy) || (ghost[a].gy + 1 == POW[b].powy && ghost[a].gx == POW[b].powx)) {
				gotoxy(POW[b].powx, POW[b].powy);
				setcolor(2, 0);
				printf("P");
			}
		}
	}
}

void superGhost_run(int x) {
	int i = 0;
	if (ghost[x].gx < hunter.x) {
		if (cursor(ghost[x].gx + 1, ghost[x].gy) == ' ' || cursor(ghost[x].gx + 1, ghost[x].gy) == 'O') {
			i = 4;
		}
		else if (cursor(ghost[x].gx + 1, ghost[x].gy) == 'x') {
			if (cursor(ghost[x].gx, ghost[x].gy - 1) == 'x' && cursor(ghost[x].gx, ghost[x].gy + 1) == ' ') {
				i = 2;
			}
			else if (cursor(ghost[x].gx, ghost[x].gy - 1) == ' ' && cursor(ghost[x].gx, ghost[x].gy + 1) == 'x') {
				i = 1;
			}
			else if (cursor(ghost[x].gx, ghost[x].gy - 1) == ' ' && cursor(ghost[x].gx, ghost[x].gy + 1) == ' ') {
				if (ghost[x].gy < hunter.y) {
					i = 2;
				}
				else if (ghost[x].gy > hunter.y) {
					i = 1;
				}
				else {
					i = rand() % 2 + 1;
				}
			}
		}
	}
	if (ghost[x].gx > hunter.x) {
		if (cursor(ghost[x].gx - 1, ghost[x].gy) == ' ' || cursor(ghost[x].gx - 1, ghost[x].gy) == 'O') {
			i = 3;
		}
		else if (cursor(ghost[x].gx - 1, ghost[x].gy) == 'x') {
			if (cursor(ghost[x].gx, ghost[x].gy - 1) == 'x' && cursor(ghost[x].gx, ghost[x].gy + 1) == ' ') {
				i = 2;
			}
			else if (cursor(ghost[x].gx, ghost[x].gy - 1) == ' ' && cursor(ghost[x].gx, ghost[x].gy + 1) == 'x') {
				i = 1;
			}
			else if (cursor(ghost[x].gx, ghost[x].gy - 1) == ' ' && cursor(ghost[x].gx, ghost[x].gy + 1) == ' ') {
				if (ghost[x].gy < hunter.y) {
					i = 2;
				}
				else if (ghost[x].gy > hunter.y) {
					i = 1;
				}
				else {
					i = rand() % 2 + 1;
				}
			}
		}
	}
	else if (ghost[x].gx == hunter.x) {
		if (ghost[x].gy > hunter.y) {
			if (cursor(ghost[x].gx, ghost[x].gy - 1) == ' ' || cursor(ghost[x].gx, ghost[x].gy - 1) == 'O') {
				i = 1;
			}
			else if (cursor(ghost[x].gx, ghost[x].gy - 1) == 'x') {
				i = rand() % 2 + 3;
			}
		}
		else if (ghost[x].gy < hunter.y) {
			if (cursor(ghost[x].gx, ghost[x].gy + 1) == ' ' || cursor(ghost[x].gx, ghost[x].gy + 1) == 'O') {
				i = 2;
			}
			else if (cursor(ghost[x].gx, ghost[x].gy + 1) == 'x') {
				i = rand() % 2 + 3;
			}
		}
	}
	if (i == 3) {//left
		if (cursor(ghost[x].gx - 1, ghost[x].gy) == 'x' || (ghost[x].gx == 1)) {
			draw_superGhost(ghost[x].gx, ghost[x].gy);
		}
		else {
			del_draw(ghost[x].gx, ghost[x].gy);
			draw_superGhost(--ghost[x].gx, ghost[x].gy);
		}
	}
	if (i == 4) {//right
		if (cursor(ghost[x].gx + 1, ghost[x].gy) == 'x' || (ghost[x].gx == 50)) {
			draw_superGhost(ghost[x].gx, ghost[x].gy);
		}
		else {
			del_draw(ghost[x].gx, ghost[x].gy);
			draw_superGhost(++ghost[x].gx, ghost[x].gy);
		}
	}
	if (i == 1) {//up
		if (cursor(ghost[x].gx, ghost[x].gy - 1) == 'x' || (ghost[x].gy == 1)) {
			draw_superGhost(ghost[x].gx, ghost[x].gy);
		}
		else {
			del_draw(ghost[x].gx, ghost[x].gy);
			draw_superGhost(ghost[x].gx, --ghost[x].gy);
		}
	}
	if (i == 2) {//down
		if (cursor(ghost[x].gx, ghost[x].gy + 1) == 'x' || (ghost[x].gy == 25)) {
			draw_superGhost(ghost[x].gx, ghost[x].gy);
		}
		else {
			del_draw(ghost[x].gx, ghost[x].gy);
			draw_superGhost(ghost[x].gx, ++ghost[x].gy);
		}
	}
	for (int b = 0; b <= 29; b++) { //if ghost hit point then nothing happen
		if ((ghost[x].gy - 1 == point[b].py && ghost[x].gx == point[b].px) || (ghost[x].gx - 1 == point[b].px && ghost[x].gy == point[b].py) ||
			(ghost[x].gx + 1 == point[b].px && ghost[x].gy == point[b].py) || (ghost[x].gy + 1 == point[b].py && ghost[x].gx == point[b].px)) {
			gotoxy(point[b].px, point[b].py);
			setcolor(3, 0);
			printf(".");
		}
	}
	for (int b = 0; b <= 1; b++) { //if ghost hit power then nothing happen
		if ((ghost[x].gy - 1 == POW[b].powy && ghost[x].gx == POW[b].powx) || (ghost[x].gx - 1 == POW[b].powx && ghost[x].gy == POW[b].powy) ||
			(ghost[x].gx + 1 == POW[b].powx && ghost[x].gy == POW[b].powy) || (ghost[x].gy + 1 == POW[b].powy && ghost[x].gx == POW[b].powx)) {
			gotoxy(POW[b].powx, POW[b].powy);
			setcolor(2, 0);
			printf("P");
		}
	}
}

void score() {//show score
	gotoxy(2, 27);
	setcolor(7, 0);
	printf("SCORE : %d", sc);
}

void life_point() {//show LP
	gotoxy(15, 27);
	setcolor(7, 0);
	printf("LP : %d", lp);
}

void show_power() {//show power
	gotoxy(42, 27);
	setcolor(7, 0);
	printf("POWER : %d", pHunter);
}

void player() {//show player name
	gotoxy(26, 27);
	setcolor(7, 0);
	cout << name;
}

int main() {
	setcursor(0);
	srand(time(NULL));
	while (true) {
		int exitState = 0;
		int menuState = 0;
		int scoreState = 0;
		char ch1 = ' ';
		lp = 3;
		sc = 0;
		pt = 30;
		pHunter = 0;
		countPower = 2;
		countWalk = 0;
		timePower = 0;
		main_menu();
		ch1 = _getch();
		//exit menu
		if (ch1 == 'x') {
			while (true) {
				char ch1 = ' ';
				if (exitState == 0) {
					exit_menu();
					ch1 = _getch();
					if (ch1 == 'p') {
						main_menu();
						menuState = 1;
						exitState = 2;
					}
					else if (ch1 == 'x') {
						exitState = 1;
						break;
					}
				}
				if (menuState == 1) {
					main_menu();
					ch1 = _getch();
					if (ch1 == 'x') {
						exitState = 0;
					}
					else if (ch1 == 's') {
						score_board();
					}
					else {
						exitState = 2;
						break;
					}
				}
			}
		}
		//score board
		if (ch1 == 's') {
			while (true) {
				char ch1 = ' ';
				if (scoreState == 0) {
					score_board();
					main_menu();
					menuState = 1;
					scoreState = 2;
				}
				if (menuState == 1) {
					main_menu();
					ch1 = _getch();
					if (ch1 == 's') {
						scoreState = 0;
					}
					else if (ch1 == 'x') {
						exitState = 1;
						menuState = 0;
					}
					else {
						break;
					}
				}
				if (exitState == 1) {
					exit_menu();
					ch1 = _getch();
					if (ch1 == 'p') {
						main_menu();
						menuState = 1;
						exitState = 2;
					}
					else if (ch1 == 'x') {
						exitState = 1;
						break;
					}
				}
			}
		}
		//quit game
		if (exitState == 1) {
			break;
		}
		player_name();
		char ch = ' ';
		randomMap = 1;
		if (randomMap == 1) {
			draw_map1();
			//hunter map 1
			hunter = { 4,4 };
			//ghost position map 1
			ghost[0] = { 1,9 };//super ghost
			ghost[1] = { 14, 15 };//super ghost
			ghost[2] = { 31, 15 };//super ghost
			ghost[3] = { 41, 13 };//super ghost
			ghost[4] = { 32, 25 };
			ghost[5] = { 1,17 };
			ghost[6] = { 16,7 };
			ghost[7] = { 16,25 };
			ghost[8] = { 23,1 };
			ghost[9] = { 24,9 };
			ghost[10] = { 26,20 };
			ghost[11] = { 2,1 };
			ghost[12] = { 32,4 };
			ghost[13] = { 8,10 };
			ghost[14] = { 6,23 };
			ghost[15] = { 43,6 };
			ghost[16] = { 44,22 };
			ghost[17] = { 50,1 };
			//point position map 1
			point[0] = { 1,1 };
			point[1] = { 9,3 };
			point[2] = { 2,20 };
			point[3] = { 6,17 };
			point[4] = { 8,8 };
			point[5] = { 8,12 };
			point[6] = { 9,23 };
			point[7] = { 13,20 };
			point[8] = { 17,19 };
			point[9] = { 18,22 };
			point[10] = { 20,5 };
			point[11] = { 20,9 };
			point[12] = { 23,13 };
			point[13] = { 27,18 };
			point[14] = { 28,5 };
			point[15] = { 28,25 };
			point[16] = { 29,10 };
			point[17] = { 32,1 };
			point[18] = { 34,15 };
			point[19] = { 35,6 };
			point[20] = { 37,10 };
			point[21] = { 37,19 };
			point[22] = { 38,1 };
			point[23] = { 44,12 };
			point[24] = { 44,25 };
			point[25] = { 46,2 };
			point[26] = { 46,8 };
			point[27] = { 46,17 };
			point[28] = { 50,5 };
			point[29] = { 50,21 };
			//power position map 1
			POW[0] = { 10,16 };
			POW[1] = { 38,14 };
		}
		for (int a = 0; a <= 3; a++) {
			draw_superGhost(ghost[a].gx, ghost[a].gy);
		}
		for (int a = 4; a <= 17; a++) {
			draw_ghost(ghost[a].gx, ghost[a].gy);
		}
		draw_point();
		draw_power(0);
		draw_power(1);
		draw_hunter(hunter.x, hunter.y);
		do {
			score();
			life_point();
			show_power();
			player();
			if (_kbhit()) { //keyboard check
				ch = _getch();
				ghost_run();
				superGhost_run(0);
				superGhost_run(1);
				superGhost_run(2);
				superGhost_run(3);
				if (ch == 'a') {
					if (hunter.x == 1) {//if x,y = condition then continue
						draw_hunter(hunter.x, hunter.y);
					}
					else {
						if (cursor(--hunter.x, hunter.y) == 'x') { //if hunter hit the wall then continue
							draw_hunter(++hunter.x, hunter.y);
						}
						else {
							del_draw(++hunter.x, hunter.y);
							draw_hunter(--hunter.x, hunter.y);
						}
					}
				}
				if (ch == 'd') {
					if (hunter.x == 50) {//if x,y = condition then continue
						draw_hunter(hunter.x, hunter.y);
					}
					else {
						if (cursor(++hunter.x, hunter.y) == 'x') { //if hunter hit the wall then continue
							draw_hunter(--hunter.x, hunter.y);
						}
						else {
							del_draw(--hunter.x, hunter.y);
							draw_hunter(++hunter.x, hunter.y);
						}
					}
				}
				if (ch == 'w') {
					if (hunter.y == 1) {//if x,y = condition then continue
						draw_hunter(hunter.x, hunter.y);
					}
					else {
						if (cursor(hunter.x, --hunter.y) == 'x') { //if hunter hit the wall then continue
							draw_hunter(hunter.x, ++hunter.y);
						}
						else {
							del_draw(hunter.x, ++hunter.y);
							draw_hunter(hunter.x, --hunter.y);
						}
					}
				}
				if (ch == 's') {
					if (hunter.y == 25) {
						draw_hunter(hunter.x, hunter.y);
					}
					else {
						if (cursor(hunter.x, ++hunter.y) == 'x') { //if hunter hit the wall then continue
							draw_hunter(hunter.x, --hunter.y);
						}
						else {
							del_draw(hunter.x, --hunter.y);
							draw_hunter(hunter.x, ++hunter.y);
						}
					}
				}
				fflush(stdin); //clear keyboard buffer

				//if hunter walk past super ghost then print super ghost
				for (int b = 0; b <= 3; b++) {
					if ((hunter.x - 1 == ghost[b].gx && hunter.y == ghost[b].gy) || (hunter.x + 1 == ghost[b].gx && hunter.y == ghost[b].gy) ||
						(hunter.y - 1 == ghost[b].gy && hunter.x == ghost[b].gx) || (hunter.y + 1 == ghost[b].gy && hunter.x == ghost[b].gx)) {
						draw_superGhost(ghost[b].gx, ghost[b].gy);
					}
				}

				//if hunter walk past ghost then print ghost
				for (int b = 4; b <= 17; b++) {
					if ((hunter.x - 1 == ghost[b].gx && hunter.y == ghost[b].gy) || (hunter.x + 1 == ghost[b].gx && hunter.y == ghost[b].gy) ||
						(hunter.y - 1 == ghost[b].gy && hunter.x == ghost[b].gx) || (hunter.y + 1 == ghost[b].gy && hunter.x == ghost[b].gx)) {
						draw_ghost(ghost[b].gx, ghost[b].gy);
					}
				}

				//count score
				for (int i = 0; i <= 29; i++) {
					if (hunter.x == point[i].px && hunter.y == point[i].py) {
						sc += 100;
						pt -= 1;
						point[i].px = 52;
						point[i].py = 52;
					}
				}

				//count lp and respawn hunter
				for (int b = 0; b <= 17; b++) {
					if ((hunter.x == ghost[b].gx && hunter.y == ghost[b].gy && pHunter == 0)) {
						lp -= 1;
						if (randomMap == 1) {//map1
							hunter.x = 4;
							hunter.y = 4;
						}
					}
				}

				//count power
				for (int b = 0; b <= 1; b++) {
					if (hunter.x == POW[b].powx && hunter.y == POW[b].powy) {
						if (pHunter == 1) {
							countPower -= 1;
							sc += 200;
							POW[b].powx = 52;
							POW[b].powy = 52;
						}
						else {
							pHunter += 1;
							sc += 200;
							countPower -= 1;
							POW[b].powx = 52;
							POW[b].powy = 52;
						}
					}
				}

				//if hunter hit ghost then respawn ghost
				for (int b = 0; b <= 17; b++) {
					if (hunter.x == ghost[b].gx && hunter.y == ghost[b].gy && pHunter == 1) {
						sc += 300;
						pHunter -= 1;
						if (randomMap == 1) {//If map1
							ghost[b].gx = 21;
							ghost[b].gy = 17;
						}
					}
				}

				//count walk
				if (countPower <= 1) {
					countWalk++;
				}

				//drop power
				if (countWalk == 100) {
					countWalk -= 100;
					if (countPower == 2) {
						continue;
					}
					if (countPower == 1) {
						if (randomMap == 1) {
							if (cursor(10, 16) == ' ') {
								POW[0] = { 10,16 };
								draw_power(0);
							}
							else if (cursor(38, 14) == ' ') {
								POW[1] = { 38,14 };
								draw_power(1);
							}
						}
						countPower += 1;
					}
					if (countPower == 0) {
						if (randomMap == 1) {
							POW[0] = { 10,16 };
							POW[1] = { 38,14 };
							draw_power(0);
							draw_power(1);
						}
						countPower += 2;
					}
				}

				//time of power
				if (pHunter == 1) {
					timePower += 1;
				}
				if (timePower == 50) {
					timePower = 0;
					pHunter = 0;
				}
			}
			Sleep(100);
		} while (ch != 'x' && lp != 0 && pt != 0);
		game_over();
		score_board();
	}
	return 0;
}