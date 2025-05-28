# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 15:57:24 by vsarana           #+#    #+#              #
#    Updated: 2025/04/15 15:57:25 by vsarana          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
CCFLAGS = -Wall -Wextra -Werror -std=c++98
INCLUDES = -Iclass

NAME = bureaucrat

SRC_DIRS = . class_imp
OBJ_DIR = obj
SRCS = main.cpp $(wildcard class_imp/*.cpp)
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)


GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CCFLAGS) $(INCLUDES) -o $@ $^
	@echo "$(GREEN)Compilation finished successfully!$(NC)"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)All object files have been removed.$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Executable file has been removed.$(NC)"

re: fclean all

.PHONY: all clean fclean re