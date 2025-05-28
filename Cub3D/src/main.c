/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:37:34 by rukoltso          #+#    #+#             */
/*   Updated: 2024/11/28 13:59:24 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	game_loop(t_game *game)
{
	load_textures(game);
	raycasting(game);
	render(game);
	setup_input(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	mlx_loop_hook(game->mlx, update_frame, game);
	mlx_loop(game->mlx);
}

int	check_arg(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
		return (print_error("Usage: <program_name> <map_file>"));
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len - 4] != '.' || argv[1][len - 3] != 'c' ||
		argv[1][len - 2] != 'u' || argv[1][len - 1] != 'b')
		return (print_error("Error\nIncorrect file extension!"));
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!check_arg(ac, av))
		return (1);
	if (!init_game(&game))
	{
		free_game(&game);
		return (1);
	}
	if (!parse_file(av[1], &game))
	{
		free_game(&game);
		return (1);
	}
	game_loop(&game);
	free_game(&game);
	return (0);
}
