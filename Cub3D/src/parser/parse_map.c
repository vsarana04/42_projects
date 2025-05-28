/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:11:27 by rukoltso          #+#    #+#             */
/*   Updated: 2024/11/18 19:41:34 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	validate_char(t_map *map, t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			c = map->map[i][j];
			if (!is_map_char(c))
				return (print_error("Error\nInvalid character"));
			if ((c == 'N' || c == 'S' || c == 'E' || c == 'W')
				&& !set_player_position(game, c, j, i))
				return (0);
			j++;
		}
		i++;
	}
	if (game->map_flags.player_count != 1)
		return (print_error("Error\nMap must contain one player"));
	return (1);
}

int	parse_map(t_game *game)
{
	if (!finalize_map(game))
		return (print_error("Error\nFailed to finalize map padding"));
	if (!validate_char(&game->map, game))
		return (print_error("Error\nInvalid characters"));
	if (!validate_closed_map(&game->map, game))
		return (print_error("Error\nMap is not closed or player on edge"));
	return (1);
}
