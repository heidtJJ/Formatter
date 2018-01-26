CC = gcc
FLAGS = -g 
EXEC = formatter
TEXT = shakespeare
OBJ = formatter.o list.o

$(EXEC): formatter.o list.o
	$(CC) $(FLAGS) -o $(EXEC) $(OBJ)

formatter.o: formatter.c
	$(CC) $(FLAGS) -c formatter.c

list.o: list.c
	$(CC) $(FLAGS) -c list.c

test-me:
	./$(EXEC) $(TEXT).txt out.txt 50

clean:
	rm -f $(EXEC) $(OBJ)
