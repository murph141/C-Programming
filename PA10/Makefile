GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = pa10.o answer10.o tree.o
HDRS = pa10.h tree.h
TARGET = pa10
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

pa10: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -rf *.o $(TARGET)
