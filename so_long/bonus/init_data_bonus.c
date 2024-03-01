/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:25:23 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/11 15:00:59 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void	init_img(t_game *game)
{
	int	i;
	int	j;

	i = 50;
	j = 50;
	game->floor = mlx_xpm_file_to_image(game->mlx_ptr,
			"game_images/floor.xpm", &i, &j);
	game->walls = mlx_xpm_file_to_image(game->mlx_ptr,
			"game_images/wall.xpm", &i, &j);
	game->ex = mlx_xpm_file_to_image(game->mlx_ptr,
			"game_images/exit.xpm", &i, &j);
	game->bee = mlx_xpm_file_to_image(game->mlx_ptr,
			"game_images/player.xpm", &i, &j);
	game->item = mlx_xpm_file_to_image(game->mlx_ptr,
			"game_images/item.xpm", &i, &j);
	game->enemy = mlx_xpm_file_to_image(game->mlx_ptr,
			"game_images/enemy.xpm", &i, &j);
}

void	*get_image(t_game *game, char c)
{
	void	*image;

	if (c == 'C')
		image = game->item;
	if (c == 'E')
		image = game->ex;
	if (c == '1')
		image = game->walls;
	if (c == '0')
		image = game->floor;
	if (c == 'P')
		image = game->bee;
	if (c == 'H')
		image = game->enemy;
	return (image);
}

void	init_data(t_game *game)
{
	int		i;
	int		j;
	void	*image;

	i = 0;
	j = 50;
	game->x = 0;
	game->y = 0;
	while (game->map[i])
	{
		if (game->map[i] == '\n')
		{
			game->x = 0;
			game->y += j;
			i++;
			continue ;
		}
		if (game->error_flag == 0)
			image = get_image(game, game->map[i]);
		if (image != NULL)
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
					image, game->x, game->y);
		game->x += j;
		i++;
	}
}
