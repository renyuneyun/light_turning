#include <stdio.h>
#include "control.h"
#include <errno.h>

extern int kbd;
void jmdelay(int n) {
	int i,j,k;
	for (i=0;i<n;i++)
		for (j=0;j<100;j++)
			for (k=0;k<100;k++);
}

int tube_show(char num[2])
{
	int fd;
	int NUM[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};
	int i = num[0] - '0', j = num[1] - '0';
	printf("%d%d\n", i, j);
	fd = open(LED,O_RDWR);
	ioctl(fd, 0x12, (NUM[i] << 8)|NUM[j]);
	close(fd);
	return 0;
}
int dot_show(unsigned char mat[8][8])
{
	int fd;
	unsigned char real[8] = {0};
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++)
			printf("%d", mat[i][j]);
		printf("\n");
	}
	for (i = 7; i > -1; i--) {
		for (j = 0; j < 8; j++) {
			real[j] = ((real[j] << 1) | mat[i][j]);
		}
	}
	fd = open(LED, O_RDWR);
	ioctl(fd, 0x11, real);
	for (i = 0; i < 8; i++) {
		write(fd, real, 8);
	}
	close(fd);
	return 0;
}

unsigned short scancodes[64];
KeyMap keymap[] = {
	{KEY_KP0,  0x0b},
	{KEY_KP1,  0x02},
	{KEY_KP2,  0x03},
	{KEY_KP3,  0x04},
	{KEY_KP4,  0x05},
	{KEY_KP5,  0x06},
	{KEY_KP6,  0x07},
	{KEY_KP7,  0x08},
	{KEY_KP8,  0x09},
	{KEY_KP9,  0x0a},

	{KEY_NUMLOCK,   0x2a},
	{KEY_KP_DIVIDE, 0x35},
	{KEY_KP_MULTIPLY,   0x37},
	{KEY_KP_MINUS,  0x4a},
	{KEY_KP_PLUS,       0x4e},
	{KEY_KP_ENTER,  0x1c},
	{KEY_KP_DEL,    0x53},
};

int kbd_init()
{
	int fd;
	int i;
	//fd = open(KEYBOARD, O_RDONLY | O_NONBLOCK);
	fd = open(KEYBOARD, O_RDONLY);
	if (fd < 0) {
		printf("%s - Can't open keyboard!\n", __FUNCTION__);
		return -1;
	}
	for (i = 0; i < sizeof(scancodes) / sizeof(scancodes[0]); i++)
		scancodes[i] = KEY_UNKNOWN;
	for (i = 0; i < sizeof(keymap) / sizeof(keymap[0]); i++)
		scancodes[keymap[i].scancode] = keymap[i].key;
	kbd = fd;
	return fd;
}

int kbd_close()
{
	return close(kbd);
}

int kbd_read(char* kbuf)
{
	int keydown = 0;
	int cc = 0;
	char buf;
	cc = read(kbd, &buf, 1);
	if (cc < 0) {
		if ((errno != EINTR) && (errno != EAGAIN) && (errno != EINVAL)) {
			perror("KBD KEY");
			return (-1);
		} else {
			return (0);
		}
	}
	if (cc == 0)
		return 0;
	/* If the code is bigger than 127, then we know that */
	/* we have a key down.  Figure out what we've got */
	if (buf & 0x80) {
		keydown = 1;    /* Key pressed but not released */
	} else {
		keydown = 2;    /* key released */
	}
	buf &= (~0x80);
	*kbuf = scancodes[(int) buf];
	return keydown;
}

char get_key()
{
	int keydown = 0;
	char key = 0;
	unsigned short scancode;
	while (1) {
		keydown = kbd_read(&key); //block read
		if (keydown == 1){//key press down  2: key up
			printf("KEY: %d\n", key);
			return key;
		}
	}
}

