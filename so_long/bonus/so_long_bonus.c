/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:16:12 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/11 18:11:16 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long_bonus.h"

void	destroy(t_game	*game)
{
	if (game)
	{
		if (game->map)
			free(game->map);
		if (game->floor)
			mlx_destroy_image(game->mlx_ptr, game->floor);
		if (game->walls)
			mlx_destroy_image(game->mlx_ptr, game->walls);
		if (game->ex)
			mlx_destroy_image(game->mlx_ptr, game->ex);
		if (game->bee)
			mlx_destroy_image(game->mlx_ptr, game->bee);
		if (game->enemy)
			mlx_destroy_image(game->mlx_ptr, game->enemy);
		if (game->item)
			mlx_destroy_image(game->mlx_ptr, game->item);
		if (game->win_ptr)
			mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		if (game->mlx_ptr)
			free(game->mlx_ptr);
		free(game);
	}
}

int	check_arg(int argc, char **argv, t_game	*game)
{
	size_t	len;

	if (argc != 2)
	{
		ft_printf("ERROR\nCheck the arguments!\n");
		destroy(game);
		exit(1);
	}
	len = ft_strlen(argv[1]);
	if (argv[1][len - 4] != '.' || argv[1][len - 3] != 'b' || \
			argv[1][len - 2] != 'e' || argv[1][len - 1] != 'r')
	{
		ft_printf("ERROR\nIncorrect extension!\n");
		destroy(game);
		exit(1);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (0);
	game->mlx_ptr = mlx_init();
	check_arg(argc, argv, game);
	read_map(argv[1], game);
	validate_map(game);
	init_img(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			(game->width - 1) * 50, game->height * 50, "so_long");
	init_data(game);
	mlx_key_hook(game->win_ptr, key_press, game);
	mlx_hook(game->win_ptr, 17, 0, (void *)exit, 0);
	mlx_loop(game->mlx_ptr);
	destroy(game);
	return (0);
}
