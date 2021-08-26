#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

//ghostHunter

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

void score() {//show score

}

int main() {
	setcursor(0);
	draw_map();
	char ch = ' ';
	int x = 4, y = 4;
	draw_hunter(x, y);
	do {
		if (_kbhit()) { //keyboard check
			ch = _getch();
			if (ch == 'a') {
				if (x == 1) {//if x,y = condition then continue
					continue;
				}
				else {
					if (cursor(--x, y) == 'x') {
						draw_hunter(++x, y);
					}
					else {
						del_draw(++x, y);
						draw_hunter(--x, y);
					}
				}
			}
			if (ch == 'd') {
				if (x == 50) {//ถ้า x=50 จะไม่เกิดอะไรขึ้น
					continue;
				}
				else {
					if (cursor(++x, y) == 'x') {
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
					if (cursor(x, ++y) == 'x') {
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