#CFLAGS	= +cpm -Wall --list --c-code-in-asm  -DGCC
CFLAGS	= +cpm -Wall -DGCC
LINKOP	= +cpm -create-app -lmath48
DESTDIR = ~/HostFileBdos/c/
DESTDIR1 = /var/www/html
SUM = sum
CP = cp
INDENT = indent -kr
SUDO = sudo

all: clock

clock: clock.o liboled.o font.o sysface.o
	zcc $(LINKOP) -oclock clock.o liboled.o font.o sysface.o $(SNAP)

sysface.o: sysface.c
	zcc $(CFLAGS) -c sysface.c

clock.o: clock.c
	date > date.h
	zcc $(CFLAGS) -c clock.c

liboled.o: liboled.c
	zcc $(CFLAGS) -c liboled.c

font.o: font.c
	zcc $(CFLAGS) -c font.c

clean:
	$(RM) *.o *.err *.lis *.def *.lst *.sym *.exe *.COM  *.map clock

just:
	$(INDENT) clock.c
	$(INDENT) font.c
	$(INDENT) liboled.c 
	$(INDENT) sysface.c 

scope:
	cscope

install:
	$(SUDO) $(CP) ./*.COM $(DESTDIR1)/. 
	$(CP) CLOCK.COM $(DESTDIR)clock.com

check:
	$(SUM) *.COM

