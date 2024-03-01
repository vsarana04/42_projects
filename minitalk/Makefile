# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsarana <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/24 11:27:25 by vsarana           #+#    #+#              #
#    Updated: 2023/08/24 15:06:03 by vsarana          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client
NAME_S = server
NAME_BC = client_bonus
NAME_BS = server_bonus

PRINTF = ft_printf

CLIENT = client.c
SERVER = server.c
CLIENT_B = client_bonus.c
SERVER_B = server_bonus.c

OBJ_C = ${CLIENT:.c=.o}
OBJ_S = ${SERVER:.c=.o}
OBJ_BC = ${CLIENT_B:.c=.o}
OBJ_BS = ${SERVER_B:.c=.o}

CC			= cc
CFLAGS		= -Wall -Werror -Wextra 
INCLUDE = -I inc
RM = rm -rf

all:	$(NAME_C) $(NAME_S)

$(NAME_C) : $(OBJ_C) $(OBJ_S)
		@make -C ft_printf
		$(CC) $(CFLAGS) $(OBJ_C) $(INCLUDE) -Lft_printf -lftprintf -o $(NAME_C)
		$(CC) $(CFLAGS) $(OBJ_S) $(INCLUDE) -Lft_printf -lftprintf -o $(NAME_S)

bonus:  $(NAME_BC) $(NAME_BS)

$(NAME_BC) : $(OBJ_BC) $(OBJ_BS)
		make -C ft_printf
		$(CC) $(CFLAGS) $(OBJ_BC) $(INCLUDE) -Lft_printf -lftprintf -o $(NAME_BC)
		$(CC) $(CFLAGS) $(OBJ_BS) $(INCLUDE) -Lft_printf -lftprintf -o $(NAME_BS)

$(OBJ_C) $(OBJ_S) $(OBJ_BC) $(OBJ_BS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
		@make clean -C ft_printf
		${RM} ${OBJ_C}
		${RM} ${OBJ_S}
		${RM} ${OBJ_BC}
		${RM} ${OBJ_BS}



fclean : clean
		@make fclean -C ft_printf
		${RM} $(NAME_C)
		${RM} $(NAME_S)
		${RM} $(NAME_BC)
		${RM} $(NAME_BS)

re : fclean all

.PHONY:		all bonus clean fclean re
