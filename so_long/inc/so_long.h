/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:20:27 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/11 19:23:41 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h> 
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_game
{
	void	*mlx_ptr;	
	void	*win_ptr;
	void	*floor;
	void	*walls;
	void	*bee;
	void	*item;
	void	*ex;
	int		height;
	int		width;
	int		collect;
	int		exit;
	int		player;
	int		wall;
	int		back;
	int		error_flag;
	int		x;
	int		y;
	int		steps;
	char	*map;

}	t_game;

void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(char *s);
void	check_map_dimension(int fd, char **line, t_game *game);
void	update_buffer(char *line, t_game *game);
void	read_map(char *map, t_game *game);
void	check_components(t_game	*game);
void	count_components(t_game *game);
void	check_verticall(t_game *game);
void	check_horizontall(t_game *game);
void	validate_map(t_game *game);
void	init_img(t_game *game);
void	*get_image(t_game *game, char c);
void	init_data(t_game *game);
void	check_win(t_game *game);
void	move_player(t_game *game, int offset);
int		key_press(int key, t_game *game);
void	destroy(t_game *game);

#endif
