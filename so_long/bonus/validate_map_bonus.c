/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:37:34 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/13 13:23:37 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void	check_components(t_game	*game)
{
	if (game->collect < 1 || game->exit != 1
		|| game->player != 1 || game->chameleon < 1)
	{
		ft_printf("ERROR\nCheck the components!\n");
		exit(1);
	}
}

void	count_components(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (game->map[i] != 'C' && game->map[i] != 'E'
			&& game->map[i] != '1' && game->map[i] != '0'
			&& game->map[i] != 'P' && game->map[i] != 'H'
			&& game->map[i] != '\n')
			exit(1);
		if (game->map[i] == 'C')
			game->collect++;
		if (game->map[i] == 'E')
			game->exit++;
		if (game->map[i] == '1')
			game->wall++;
		if (game->map[i] == '0')
			game->back++;
		if (game->map[i] == 'P')
			game->player++;
		if (game->map[i] == 'H')
			game->chameleon++;
		i++;
	}
	check_components(game);
}

void	check_verticall(t_game *game)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(game->map);
	i = game->width - 2;
	j = game->width;
	while (i < len && j < len)
	{
		if (game->map[i] != '1' )
		{
			game->error_flag = 1;
			ft_printf("ERROR\nSomething is wrong with the right wall!\n");
			exit(1);
		}
		if (game->map[j] != '1')
		{
			game->error_flag = 1;
			ft_printf("ERROR\nSomething is wrong with the left wall!\n");
			exit(1);
		}
		i += game->width;
		j += game->width;
	}
}

void	check_horizontall(t_game *game)
{
	int	i;
	int	j;
	int	len;

	len = ft_strlen(game->map);
	i = 0;
	j = len - game->width;
	while (i < game->width && j < len)
	{
		if (game->map[i] != '1' && game->map[i] != '\n')
		{
			game->error_flag = 1;
			ft_printf("ERROR\nSomething is wrong with the upper wall!\n");
			exit(1);
		}
		if (game->map[j] != '1' && game->map[j] != '\n')
		{
			game->error_flag = 1;
			ft_printf("ERROR\nSomething is wrong with the bottom wall!\n");
			exit(1);
		}
		i++;
		j++;
	}
}

void	validate_map(t_game *game)
{
	check_horizontall(game);
	check_verticall(game);
	count_components(game);
}
