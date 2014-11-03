#include <stdio.h>
#include <math.h>
#include "control.h"
#include "defs.h"

#define DEBUG(M) printf("%s\n", #M);

int x = 0, y = 0;
unsigned char mat[8][8];
char diff[3][3] = {{1, 1, 1},
				{1, 0, 1},
				{1, 1, 1}};
int dots = 0;
int kbd;
int steps = 0;

int init();
int endln();
int move(char key);
void cgmat(unsigned char mat[8][8], char diff[3][3], int *dots);
int done();
void listen_key();

int main(int argc, char **argv) {
	init();
	listen_key();
	endln();
	return 0;
}

int init()
{
	int i, j;
	char ch[2] = {'0', '0'};
	kbd_init();
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			mat[i][j] = 0;
	mat[0][1] = mat[1][0] = mat[1][1] = 1;
	dots = 3;
	tube_show(ch);
	dot_show(mat);
	return 0;
}

int endln()
{
	kbd_close();
	return 0;
}

int move(char key)
{
	const int mvcmd[8] = {'2', '4', '6', '8', '1', '3', '7', '9'};
	const int movements[8][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}, {1, -1}, {1, 1}, {-1, -1}, {-1, 1}};
	const char cg[4] = {'0', '5', KEY_KP_DEL, KEY_KP_ENTER};
	int i;
	char ch[2];
	for (i = 0; i < 4; i++) {
		if (key == cg[i])
			return -1;
	}
	for (i = 0; i < 8; i++) {
		if (key == mvcmd[i]) {
			x = (x + movements[i][0] + 8) % 8;
			y = (y + movements[i][1] + 8) % 8;
			ch[0] = x + '0';
			ch[1] = y + '0';
			tube_show(ch);
			return i;
		}
	}
	return -2;
}

void cgmat(unsigned char mat[8][8], char diff[3][3], int *dots)
{
	int i, j;
	int ix, iy;
	int newone;
	for (i = 0; i < 3; i++) {
		ix = x + i - 1;
		if ((ix > -1) && (ix < 8))
			for (j = 0; j < 3; j++) {
				iy = y + j - 1;
				if ((iy > -1) && (iy < 8)) {
					newone = (mat[ix][iy] + diff[i][j]) % 2;
					*dots += newone - mat[ix][iy];
					mat[ix][iy] = newone;
				}
			}
	}
	++steps;
}

int done()
{
	int i, j;
	if (dots == 0)
		return 1;
	return 0;
}

void listen_key()
{
	int m;
	char key;
	while (!done()) {
		if (move(get_key()) == -1) {
			cgmat(mat, diff, &dots);
			dot_show(mat);
		}
	}
}
