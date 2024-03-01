# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsarana <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/12 17:48:11 by vsarana           #+#    #+#              #
#    Updated: 2023/09/12 17:48:14 by vsarana          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_B = so_long_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Iinc/
SOURCE = src/so_long.c src/read_map.c src/validate_map.c \
			src/init_data.c src/key_press.c src/utils.c
GETNEXTLINE = get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c
FT_PRINTF = printf/ft_printf.c  printf/ft_printf.h  printf/ft_putnbr.c \
			printf/ft_putptr_hex.c  printf/ft_string.c  printf/ft_utils.c
BONUS = bonus/so_long_bonus.c bonus/read_map_bonus.c bonus/validate_map_bonus.c  \
		bonus/init_data_bonus.c bonus/key_press_bonus.c bonus/utils_bonus.c

LIBRARY = -L minilibx-linux -lmlx -lm -lX11 -lXext
MINILIBX = minilibx-linux/

all: $(NAME)

$(NAME):
	@make -s -C $(MINILIBX)
	@make -s -C printf 
	@$(CC) -g3 -fsanitize=address $(CFLAGS) $(SOURCE) $(GETNEXTLINE) $(FT_PRINTF) $(LIBRARY) -o $(NAME)
	@echo "Compilation complete!"

bonus: $(NAME_B)

$(NAME_B):
	@make -s -C $(MINILIBX)
	@make -s -C printf 
	@$(CC) $(CFLAGS) $(BONUS) $(GETNEXTLINE) $(FT_PRINTF) $(LIBRARY) -o $(NAME_B)
	@echo "Compilation bonus complete!"

clean:
	@make clean -s -C $(MINILIBX)
	@make clean -s -C printf
	@echo "Clean complete!"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME_B)
	@echo "Executable removed!"

re: fclean all

.PHONY: all bonus clean fclean re
