/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:55:02 by rukoltso          #+#    #+#             */
/*   Updated: 2024/11/28 13:57:06 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <unistd.h>

int	print_error(char *error)
{
	size_t	len;

	len = 0;
	while (error[len])
		len++;
	write(2, error, len);
	write(2, "\n", 1);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.map != NULL)
	{
		while (i < game->map.height)
		{
			free(game->map.map[i]);
			game->map.map[i] = NULL;
			i++;
		}
		free(game->map.map);
		game->map.map = NULL;
	}
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (game->texture[i].path != NULL)
		{
			free(game->texture[i].path);
			game->texture[i].path = NULL;
		}
		if (game->texture[i].img != NULL)
		{
			mlx_destroy_image(game->mlx, game->texture[i].img);
			game->texture[i].img = NULL;
		}
		i++;
	}
}
