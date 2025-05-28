/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:21:14 by vsarana           #+#    #+#             */
/*   Updated: 2024/11/18 19:53:49 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	if_digits_only(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			j = 1;
		else if (str[i] != ' ' && str[i] != ',')
			return (0);
		i++;
	}
	return (j);
}

static int	check_color(char *line, int *i)
{
	int	j;

	j = 0;
	while (line[*i] == ' ')
		(*i)++;
	if (!if_digits_only(&line[*i]))
		return (-1);
	j = ft_atoi(&line[*i]);
	while (ft_isdigit(line[*i]))
		(*i)++;
	while (line[*i] == ' ' || line[*i] == ',')
		(*i)++;
	return (j);
}

static int	valid_rgb(char *line, int values[3])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		values[j] = check_color(line, &i);
		if (values[j] == -1)
			return (print_error("Error\nInvalid RGB value!"));
		if (values[j] < 0 || values[j] > 255)
			return (print_error("Error\nRGB value out of range"));
		j++;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0')
		return (print_error("Error\nToo many RGB values"));
	return (1);
}

int	parse_rgb(char *line, t_color *color)
{
	int	values[3];

	if (!valid_rgb(line, values))
		return (0);
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	return (1);
}

int	parse_color(char *line, t_game *game)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (parse_rgb(line + 2, &game->floor_color))
		{
			game->map_flags.has_color++;
			return (1);
		}
		else
			return (print_error("Error\nInvalid floor color!"));
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (parse_rgb(line + 2, &game->ceiling_color))
		{
			game->map_flags.has_color++;
			return (1);
		}
		else
			return (print_error("Error\nInvalid ceiling color!"));
	}
	return (print_error("Error\nInvalid color identifier!"));
}
