CC     = gcc

# Apple Silicon (M1/M2/M3)
OMP_PATH = /opt/homebrew/opt/libomp
# Intel Mac — uncomment this instead:
# OMP_PATH = /usr/local/opt/libomp

CFLAGS = -Wall -O2 -std=c99 -Xpreprocessor -fopenmp -I$(OMP_PATH)/include
LDFLAGS = -L$(OMP_PATH)/lib -lomp

blur.exe: image_blur.c
	$(CC) $(CFLAGS) image_blur.c -o blur.exe $(LDFLAGS)

run: blur.exe
	./blur.exe 1 5000
	./blur.exe 2 5000
	./blur.exe 4 5000
	./blur.exe 8 5000

clean:
	rm -f blur.exe