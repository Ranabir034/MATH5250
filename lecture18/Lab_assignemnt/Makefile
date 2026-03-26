CC      = gcc
CFLAGS  = -O2 -fopenmp -Wall -Wextra
LDFLAGS = -lm

TARGET  = option

$(TARGET): test.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	@echo "=========================================="
	@echo " Running with N=10000000, threads=1,2,4,8,16"
	@echo "=========================================="
	@for t in 1 2 4 8 16; do \
		./$(TARGET) $$t 10000000; \
	done

test: $(TARGET)
	./$(TARGET) 1 1000

clean:
	rm -f $(TARGET)

.PHONY: run test clean