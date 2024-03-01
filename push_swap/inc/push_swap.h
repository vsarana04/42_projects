/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:40:02 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/11 12:43:04 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_list
{
	int	*a;
	int	*b;
	int	size_a;
	int	size_b;

}	t_list;

void	sa(t_list *list);
void	sb(t_list *list);
void	ss(t_list *list);
void	pa(t_list *list);
void	pb(t_list *list);
void	ra(t_list *list);
void	rb(t_list *list);
void	rr(t_list *list);
void	rra(t_list *list);
void	rrb(t_list *list);
void	rrr(t_list *list);
void	sort_3(t_list *list);
void	sort_5(t_list *list);
void	radix(t_list *list);
void	create_index(t_list *list);
void	fill_list(t_list *list, char **av);
void	free_memory(t_list *list, char *msg);
int		is_sorted(int *array, int size);
int		update_argc(char **av);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
char	**handle_single_arg(int *ac, char **av);
size_t	ft_strlen(const char *str);
void	check_dup(t_list *list);
int		ft_atoi_push(char *str, t_list *list);
int		is_invalid_arg(char *arg);

#endif