/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:45:57 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/12 15:32:09 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	rra(t_list *list)
{
	int	i;
	int	tmp;

	if (list->size_a > 1)
	{
		i = list->size_a;
		tmp = list->a[i - 1];
		while (i > 0)
		{
			list->a[i] = list->a[i - 1];
			i--;
		}
		list->a[i] = tmp;
		write(1, "rra\n", 4);
	}
}

void	rrb(t_list *list)
{
	int	i;
	int	tmp;

	if (list->size_b > 1)
	{
		i = list->size_b;
		tmp = list->b[i - 1];
		while (i > 0)
		{
			list->b[i] = list->b[i - 1];
			i--;
		}
		list->b[i] = tmp;
		write(1, "rrb\n", 4);
	}
}

void	rrr(t_list *list)
{
	int	i;
	int	tmp;

	if (list->size_a > 1 && list->size_b > 1)
	{
		i = list->size_a;
		tmp = list->a[i - 1];
		while (i > 0)
		{
			list->a[i] = list->a[i - 1];
			i--;
		}
		list->a[i] = tmp;
		i = list->size_b;
		tmp = list->b[i - 1];
		while (i > 0)
		{
			list->b[i] = list->b[i - 1];
			i--;
		}
		list->b[i] = tmp;
		write(1, "rrr\n", 4);
	}
}
