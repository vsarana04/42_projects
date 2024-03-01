/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:05:31 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/12 17:47:39 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	check_win(t_game *game)
{
	if (game->collect == 0)
	{
		ft_printf("You Win!\n");
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
	if (game->map[i + offset] == 'E')
	{
		check_win(game);
		return ;
	}
	game->map[i] = '0';
	game->map[i + offset] = 'P';
	game->steps++;
	ft_printf("Steps: %d\n", game->steps);
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
	return (0);
}
