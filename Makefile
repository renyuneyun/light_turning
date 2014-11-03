CC = /root/arm2410cl/arm/gui/tools/usr/local/arm/3.4.1/bin/arm-linux-gcc
#CC = gcc
CCARGS = "-lpthread"
final = game
objs = control.o

all: $(final)

$(final): main.c $(objs)
	$(CC) -o $@ $(CCARGS) $^

control.o: control.h control.c

.PHONY: clean
clean:
	rm $(objs) $(final)
