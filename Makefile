CC = gcc
CFLAGS = -Wall

OBJ = msh.o commands.o jobs.o pipe.o redirect.o prompt.o signal_handling.o

msh: $(OBJ)
	$(CC) $(OBJ) -o msh

clean:
	rm -f *.o msh