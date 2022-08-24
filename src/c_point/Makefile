CC=gcc
CFLAGS= -Wall -g -O -fPIC -I/usr/include/python3.8
RM= rm -f
.PHONY: all clean

all: point.so

clean:
	$(RM) *.o *.so

point.so: point.o
	$(LINK.c) -shared $^ -o $@

run:
	python -c "import point;print(point.x)"
