
NAME = Minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -Iinclude -Ilibft
LIBFT = libft/libft.a
LIBS = -lreadline

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[1;33m
NC = \033[0m

# Source files and directories
SRCDIR = src
SRC = $(shell find $(SRCDIR) -name '*.c')

# Object files directory
OBJ_DIR = obj/

# Object files
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN)Compiling $@!$(NC)"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) $(LIBFT) $(LIBS)
	@echo "$(YELLOW)Done!$(NC)"

$(LIBFT):
	@make -C libft > /dev/null

# Rule to create the object files directory and compile objects
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning Libft! $(NC)"
	@rm -rf $(OBJ_DIR) > /dev/null
	@make -C libft clean > /dev/null

fclean: clean
	@echo "$(RED)Cleaning $(NAME)! $(NC)"
	@rm -f $(NAME) > /dev/null
	@make -C libft fclean > /dev/null
	@echo "$(YELLOW)Done Cleaning!$(NC)"

re: fclean all

.PHONY: all clean fclean re
