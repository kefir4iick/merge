CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = mergesort
OBJS = main.o metrics.o top_down.o bottom_up.o optimized.o ten_way.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c mergesort.h
	$(CC) $(CFLAGS) -c main.c

metrics.o: metrics.c mergesort.h
	$(CC) $(CFLAGS) -c metrics.c

top_down.o: top_down.c mergesort.h
	$(CC) $(CFLAGS) -c top_down.c

bottom_up.o: bottom_up.c mergesort.h
	$(CC) $(CFLAGS) -c bottom_up.c

optimized.o: optimized.c mergesort.h
	$(CC) $(CFLAGS) -c optimized.c

ten_way.o: ten_way.c mergesort.h
	$(CC) $(CFLAGS) -c ten_way.c

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
