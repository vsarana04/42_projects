/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:22:29 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/14 14:03:02 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	check_map_dimension(int fd, char **line, t_game *game)
{
	char	*new_line;

	if (ft_strlen(*line) != game->width)
	{
		if (get_next_line(fd) == NULL && ft_strlen(*line) == game->width - 1)
		{
			new_line = ft_strjoin(*line, "\n");
			free(*line);
			*line = new_line;
		}
		else
		{
			ft_printf("ERROR\nThe map is not rectangular!\n");
			exit(1);
		}
	}
}

void	update_buffer(char *line, t_game *game)
{
	char	*tmp;

	if (line && game->map)
	{
		tmp = game->map;
		game->map = ft_strjoin(game->map, line);
		free(tmp);
	}
}

void	read_map(char *buffer, t_game *game)
{
	int		fd;
	char	*line;

	game->map = ft_strdup("");
	fd = open(buffer, O_RDONLY);
	if (fd < 0)
		exit(1);
	line = get_next_line(fd);
	while (line)
	{
		game->height++;
		if (game->height == 1)
			game->width = ft_strlen(line);
		check_map_dimension(fd, &line, game);
		update_buffer(line, game);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
