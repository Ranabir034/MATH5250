#	make
#	make clean
#	make help

CC     = gcc
FFLAGS = -Wall -Wextra -g
LFLAGS = -lm

OBJECTS = main.o       \
          create_poly.o \
          delete_poly.o \
          add_poly.o    \
          eval_poly.o   \
          print_poly.o  \
          input_poly.o

.PHONY: clean help

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe

help:
	@echo "Valid targets:"
	@echo "  main.exe      - build the executable (default)"
	@echo "  clean         - removes *.o and main.exe"

