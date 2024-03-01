NAME = push_swap

SRC = src/sort_3.c src/sort_5.c src/sort_big.c src/push_swap.c src/checking.c \
	operations/push.c operations/reverse_rotate.c operations/rotate.c \
	operations/swap.c utils/utils.c utils/utils2.c utils/utils3.c

OBJS = $(SRC:.c=.o)

LIBFT = libft/libft.a
LIBFT_DIR = libft/

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -Iinc/ -I$(LIBFT_DIR)

all: $(LIBFT) $(NAME)
	@echo "Compilation complete!"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -s -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make clean -s -C $(LIBFT_DIR)
	@echo "Clean complete!"

fclean: clean
	@rm -f $(NAME)
	@make fclean -s -C $(LIBFT_DIR)
	@echo "Executable removed!"

re: fclean all

.PHONY: all clean fclean re