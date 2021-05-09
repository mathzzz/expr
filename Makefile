src=$(wildcard *.c)
obj=$(src:.c=.o)
tgt=expr

CFLAGS=-g
LDFLAGS=-dl -dynamic

$(tgt):$(obj)
	gcc -o $@ $(obj) $(LDFLAGS) && sh test.sh
	rm -f expr

.c.o:

clean:
	rm -f *.o *.out

