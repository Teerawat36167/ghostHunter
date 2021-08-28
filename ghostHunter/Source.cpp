#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

//ghostHunter

struct ghost {
	int gx;
	int gy;
	int hp;
}ghost[6];

void draw_map() {//map
	printf("+__________________________________________________+\n");
	printf("|        xx   xx    xxx   xx       xxx    xxxxx    |\n");
	printf("| xx xxx x  x    xx xxx x xx xxx x  xx xx   x   xx |\n");
	printf("| xx xxx   xxx x xx     x xx xxx xx     x x   x  x |\n");
	printf("|     xx x     x   xxx x   x x      x x   xxx xx x |\n");
	printf("| xxx xx xxx xx  x       x     x xx x xxx xxx      |\n");
	printf("| xxx        xx xx xxxx xxxx xx  x  x         xxx x|\n");
	printf("| xxx xx xxx xx    xx   xx   xx xx xxxx xxxx xx   x|\n");
	printf("| xxx xx  xx xxx x xx x xx x     x        x     x x|\n");
	printf("|     xxx    xxx x    x    xx xx x xx x x x xxx x  |\n");
	printf("| xxx     xx     xx x xxx xx   x   xx   x   xx   x |\n");
	printf("|   xxxx xxxx xx    x      x x  xx xx x xx xxx x   |\n");
	printf("|xx x    xx    xx xx  x xx   xx x     x        xx x|\n");
	printf("|xx   xx    xx xx    xx xxxx x    xx xxxx xx x  x x|\n");
	printf("|xx xxxx xx xx    xx xx  xx    x xxx    x    xx    |\n");
	printf("|x  xxxx xx    xx xx   x  x xxx  x   xx  x x  xx x |\n");
	printf("|x xxxxx    x xxx   xx xx     x xx x  xx x xx x  x |\n");
	printf("|  xx    xxx   xx x       x x      xx      x    xx |\n");
	printf("| xxx xx xx  x    xx xx xx  x xxxx  xx xx xx xx    |\n");
	printf("| xxx xx  x xx xx  x xx xx xx   xxx     x     xxx x|\n");
	printf("|       x x    xxx x x   x   xx     xxx xx xx   x x|\n");
	printf("|xxx xx   x xx xxx     x   x x  x x xx   x  x x    |\n");
	printf("|xxx xxxxxx xx xxx x xxxx xx x xx x    x  x    xxx |\n");
	printf("|xx  x           x x    x xx      x xx xx   xx   x |\n");
	printf("|xx xx xx xxx xx x x xx    xx xx xx x   xx xx  x   |\n");
	printf("|xx    xx     xx     xxxxx    xx      x       xxxxx|\n");
	printf("+--------------------------------------------------+\n");
}

void gotoxy(int x, int y) {//go to x,y
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_hunter(int x, int y) {//draw hunter
	gotoxy(x, y);
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
	printf("W");
}

void ghost_run() {
	int i;
	for (int a=0 ; a <= 5; a++) {
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
	}
}

void score() {//show score

}

int main() {
	setcursor(0);
	draw_map();
	char ch = ' ';
	int x = 4, y = 4;
	ghost[1].gx = 32;
	ghost[1].gy = 4;
	ghost[2].gx = 26;
	ghost[2].gy = 20;
	ghost[0].gx = 6;
	ghost[0].gy = 23;
	ghost[3].gx = 13;
	ghost[3].gy = 10;
	ghost[4].gx = 1;
	ghost[4].gy = 9;
	ghost[5].gx = 16;
	ghost[5].gy = 7;
	srand(time(NULL));
	draw_hunter(x, y);
	draw_ghost(ghost[0].gx, ghost[0].gy);
	draw_ghost(ghost[1].gx, ghost[1].gy);
	draw_ghost(ghost[2].gx, ghost[2].gy);
	draw_ghost(ghost[3].gx, ghost[3].gy);
	draw_ghost(ghost[4].gx, ghost[4].gy);
	draw_ghost(ghost[5].gx, ghost[5].gy);
	do {
		if (_kbhit()) { //keyboard check
			ch = _getch();
			ghost_run();
			if (ch == 'a') {
				if (x == 1) {//if x,y = condition then continue
					continue;
				}
				else {
					if (cursor(--x, y) == 'x') { //if hunter hit the wall then continue
						draw_hunter(++x, y);
					}
					else {
						del_draw(++x, y);
						draw_hunter(--x, y);
					}
				}
			}
			if (ch == 'd') {
				if (x == 50) {//if x,y = condition then continue
					continue;
				}
				else {
					if (cursor(++x, y) == 'x') { //if hunter hit the wall then continue
						draw_hunter(--x, y);
					}
					else {
						del_draw(--x, y);
						draw_hunter(++x, y);
					}
				}
			}
			if (ch == 'w') {
				if (y == 1) {//if x,y = condition then continue
					continue;
				}
				else {
					if (cursor(x, --y) == 'x') { //if hunter hit the wall then continue
						draw_hunter(x, ++y);
					}
					else {
						del_draw(x, ++y);
						draw_hunter(x, --y);
					}
				}
			}
			if (ch == 's') {
				if (y == 25) {
					continue;
				}
				else {
					if (cursor(x, ++y) == 'x') { //if hunter hit the wall then continue
						draw_hunter(x, --y);
					}
					else {
						del_draw(x, --y);
						draw_hunter(x, ++y);
					}
				}
			}
			fflush(stdin); //ล้างค่าที่กดมาเพื่อรับการกดปุ่มครั้งต่อไป
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}