GCC = gcc
CFLAGS = -g -Wall -Wshadow
LIBS =
SOURCES = answer06.c pa06.c
TARGET = pa06

OBJS = $(patsubst %.c,%.o,$(SOURCES)) 

$(TARGET): $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(TARGET) *.o *.ppm

testall:
	@./test.sh
