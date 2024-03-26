NAME	= philo

CC 		= cc

SRC		= init.c philo.c philo_main.c utils.c utils2.c routine.c

FLAGS	= -Wall -Wextra -Werror

OBJS	= $(SRC:.c=.o)

HEADER	= philo.h

all:	$(NAME)

$(NAME):		$(OBJS) $(HEADER)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re