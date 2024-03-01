NAME = philo

SRC = src/actions.c src/checking.c src/init.c \
    src/philo.c src/threads.c src/utils.c src/utils2.c 

OBJS = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -Iinc/ -pthread -g
CC = gcc

all: $(NAME)
	@echo "Compilation complete!"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	@echo "Objects removed!"

fclean: clean
	@rm -rf $(NAME)
	@echo "Executable removed!"

re: fclean all

.PHONY: all clean fclean re
