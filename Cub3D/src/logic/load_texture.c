/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:05:19 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/18 20:18:35 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx,
				game->texture[i].path,
				&game->texture[i].width,
				&game->texture[i].height);
		if (!game->texture[i].img)
			printf("Error\nFailed to load texture");
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
				&game->texture[i].bits_per_pixel,
				&game->texture[i].line_length,
				&game->texture[i].endian);
		i++;
	}
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img.addr + (y * game->img.line_length + x
			* (game->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_floor(t_game *game)
{
	int	x;
	int	y;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(game, x, y,
				(game->floor_color.r << 16)
				| (game->floor_color.g << 8) | game->floor_color.b);
			x++;
		}
		y++;
	}
}

void	set_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(game, x, y,
				(game->ceiling_color.r << 16)
				| (game->ceiling_color.g << 8) | game->ceiling_color.b);
			x++;
		}
		y++;
	}
}

void	set_colors(t_game *game)
{
	set_floor(game);
	set_ceiling(game);
}
