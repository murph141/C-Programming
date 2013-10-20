GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS =
SOURCES = answer07.c pa07.c
TARGET = pa07

OBJS = $(patsubst %.c,%.o,$(SOURCES)) 

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(TARGET) *.o
