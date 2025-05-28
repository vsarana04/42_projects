# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 12:46:12 by vsarana           #+#    #+#              #
#    Updated: 2025/05/05 12:46:13 by vsarana          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = PmergeMe
CC          = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98

SRC_DIR     = .
OBJ_DIR     = obj

SRC         = $(SRC_DIR)/main.cpp \
			  $(SRC_DIR)/PmergeMe.cpp


OBJ         = $(OBJ_DIR)/main.o \
			  $(OBJ_DIR)/PmergeMe.o 

INCLUDES    = -I.

GREEN       = \033[0;32m
RED         = \033[0;31m
NC          = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CXXFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)
	@echo "$(GREEN)Compilation finished successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files and obj directory cleaned.$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Executable cleaned.$(NC)"

re: fclean all

.PHONY: all clean fclean re