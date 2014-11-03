#ifndef DEFS
#define DEFS

#define TUBE_IOCTROL  0x11
#define DOT_IOCTROL   0x12

#define LED "/dev/led/0raw"
#define KEYBOARD "/dev/mcu/kbd"

#define KEY_UNKNOWN 0
#define KEY_KP0		'0'
#define KEY_KP1		'1'
#define KEY_KP2		'2'
#define KEY_KP3		'3'
#define KEY_KP4		'4'
#define KEY_KP5		'5'
#define KEY_KP6		'6'
#define KEY_KP7		'7'
#define KEY_KP8		'8'
#define KEY_KP9		'9'
#define KEY_KP_DEL		0x7F
#define KEY_KP_DIVIDE		'/'
#define KEY_KP_MULTIPLY	'*'
#define KEY_KP_MINUS		'-'
#define KEY_KP_PLUS		'+'
#define KEY_KP_ENTER		13
#define KEY_KP_EQUALS		61
#define KEY_KP_NUMLOCK	0XFF

#define KEY_NUMLOCK	KEY_KP_NUMLOCK

typedef struct {
    unsigned short key;
    int scancode;
} KeyMap;

#endif
