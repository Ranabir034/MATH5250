CC      = gcc
CFLAGS  = -O2 -Wall -std=c99 -D_GNU_SOURCE -fopenmp
LDFLAGS = -lm

TARGET  = main

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(LDFLAGS)

# usage: make run THREADS=4
THREADS ?= 4
run: $(TARGET)
	./$(TARGET) $(THREADS)
	python3 plot.py

clean:
	rm -f $(TARGET) *.dat *.png