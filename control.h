#ifndef CONTROL
#define CONTROL

//#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
//#include <sys/mman.h>
#include "defs.h"

void jmdelay(int n);
int tube_show(char num[2]);
int dot_show(unsigned char dot[8][8]);

char get_key();
int kbd_init();
int kbd_close();

#endif
