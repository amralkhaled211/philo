
CC=gcc
CFLAGS=-Wall -Wextra -Werror -pthread
DEPS=philo.h
OBJ=check.o init.o philo.o utils.o
EXEC=philo

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean fclean re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXEC)

re: fclean $(EXEC)