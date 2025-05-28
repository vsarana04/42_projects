/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:12:04 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/23 16:16:13 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	key_press(int key, t_game *game)
{
	if (key == 65307)
	{
		free_game(game);
		exit(0);
	}
	if (key == 65361)
		game->player.rot_speed = -ROT_SPEED;
	if (key == 65363)
		game->player.rot_speed = ROT_SPEED;
	if (key == 119)
		game->player.move_speed = MOVE_SPEED;
	if (key == 115)
		game->player.move_speed = -MOVE_SPEED;
	if (key == 97)
		game->player.strafe_speed = -MOVE_SPEED;
	if (key == 100)
		game->player.strafe_speed = MOVE_SPEED;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == 65361 || key == 65363)
		game->player.rot_speed = 0;
	if (key == 119 || key == 115)
		game->player.move_speed = 0;
	if (key == 97 || key == 100)
		game->player.strafe_speed = 0;
	return (0);
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int	update_frame(t_game *game)
{
	update_player(game);
	raycasting(game);
	render(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	setup_input(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, update_frame, game);
}
