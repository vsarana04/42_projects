#############################################
###             CONFIG                    ###
#############################################

NAME        = ircserv
CC          = c++
RM          = rm -rf
CFLAGS      = -Wall -Werror -Wextra -std=c++98
CFLAGS		+= -g
MKDIR       = mkdir -p
INCLUDES    = -I./includes

SOURCES_DIR = src
SOURCES     = src/Channel.cpp src/client.cpp src/cmds_utils.cpp src/commands.cpp src/helper.cpp src/main.cpp src/server.cpp
OBJ_DIR     = obj
OBJS        = $(SOURCES:$(SOURCES_DIR)/%.cpp=$(OBJ_DIR)/%.o)

GREEN       = \033[0;32m
RED         = \033[0;31m
NC          = \033[0m

#############################################
###               RULES                   ###
#############################################

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^
	@echo "$(GREEN)Compilation finished successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	@$(MKDIR) $(dir $@)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)All object files have been removed.$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Executable file has been removed.$(NC)"

re: fclean all

.PHONY: all clean fclean re

