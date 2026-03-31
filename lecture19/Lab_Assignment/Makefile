CC      = gcc
CFLAGS  = -O3 -Wall -std=c99 -fopenmp
LDFLAGS = -fopenmp -lm

TARGET  = normalize
SRC     = main.c

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean