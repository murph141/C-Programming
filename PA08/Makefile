GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS = pa08.h
SOURCES = answer08.c pa08.c
TARGET = pa08

OBJS = $(patsubst %.c,%.o,$(SOURCES)) 

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(TARGET) *.o

testall: $(TARGET)
	bin/test.sh
