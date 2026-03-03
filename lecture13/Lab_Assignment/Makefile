cc = gcc
CFLAGS = -Wall -Wextra -O2
LFLAGS = -lm
OBJECTS = main.o\
		 matrix.o 

.PHONY: clean

main.exe: $(OBJECTS)
	$(cc) $(OBJECTS) $(LFLAGS) -o main.exe 

%.o : %.c
	$(cc) $(CFLAGS) -c $< -o $@

clean: 
	rm -f *.o main.exe