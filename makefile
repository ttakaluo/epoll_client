CC=gcc
CFLAGS= -Wall -I.
EXE_NAME = client
FILES = send_message.o main.o
LIBS = -lpthread
all: $(FILES)
	$(CC) -o $(EXE_NAME) $(FILES) $(CFLAGS) $(LIBS)

clean:
	rm -f *.o

run:
	./$(EXE_NAME)

rebuild: clean all run

