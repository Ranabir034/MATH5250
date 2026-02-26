CC = gcc
FFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

OBJECTS = main.o \
		  function.o \
		  displaystack.o \
		  deletestack.o	\
		  push.o \
		  pop.o	\
		  bisectionmethod.o


.PHONY: clean

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o main.exe

%.o : %.c
	$(CC) $(FFLAGS) -c $< -o $@

clean:
	rm -f *.o main.exe

