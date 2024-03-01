/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:05:31 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/13 13:25:08 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void	show_steps(t_game	*game)
{
	char	*move;

	move = ft_itoa(game->steps);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 55, 25, 0x00000, "Steps: ");
	mlx_string_put(game->mlx_ptr, game->win_ptr, 100, 25, 0x00000, move);
	if (move)
		free(move);
}

void	check_win(t_game *game, char next_step)
{
	if (next_step == 'H')
	{
		ft_printf("You Lose!\nYou were eaten by a chameleon!\n");
		destroy(game);
		exit(0);
	}
	if (game->collect == 0)
	{
		ft_printf("You win!\n");
		destroy(game);
		exit(0);
	}
	else
		ft_printf("Сollect all the collectibles first!\n");
}

void	move_player(t_game *game, int offset)
{
	int	i;

	i = 0;
	while (game->map[i] != 'P')
		i++;
	if (game->map[i + offset] == '1')
		return ;
	if (game->map[i + offset] == 'C')
		game->collect--;
	if (game->map[i + offset] == 'E' || game->map[i + offset] == 'H')
	{
		check_win(game, game->map[i + offset]);
		return ;
	}
	game->map[i] = '0';
	game->map[i + offset] = 'P';
	game->steps++;
	init_data(game);
}

int	key_press(int key, t_game *game)
{
	if (key == 65307)
	{
		destroy(game);
		exit(0);
	}		
	if (key == 119 || key == 65362)
		move_player(game, -game->width);
	if (key == 115 || key == 65364)
		move_player(game, game->width);
	if (key == 97 || key == 65361)
		move_player(game, -1);
	if (key == 100 || key == 65363)
		move_player(game, 1);
	show_steps(game);
	return (0);
}
