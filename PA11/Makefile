GCC = gcc
CFLAGS = -g -Wall -Wshadow
OBJS = pa11.o answer11.o
HDRS = pa11.h
TARGET = pa11
VALGRIND = valgrind --tool=memcheck --leak-check=full --verbose

pa11: $(OBJS) $(HDRS)
	$(GCC) $(CFLAGS) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -rf *.o $(TARGET)
