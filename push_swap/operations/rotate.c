/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:46:37 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/12 15:33:16 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	ra(t_list *list)
{
	int	i;
	int	tmp;

	if (list->size_a > 1)
	{
		i = 0;
		tmp = list->a[i];
		i++;
		while (i < list->size_a)
		{
			list->a[i - 1] = list->a[i];
			i++;
		}
		list->a[i - 1] = tmp;
		write(1, "ra\n", 3);
	}
}

void	rb(t_list *list)
{
	int	i;
	int	tmp;

	if (list->size_b > 1)
	{
		i = 0;
		tmp = list->b[i];
		i++;
		while (i < list->size_b)
		{
			list->b[i - 1] = list->b[i];
			i++;
		}
		list->b[i - 1] = tmp;
		write(1, "rb\n", 3);
	}
}

void	rr(t_list *list)
{
	int	i;
	int	tmp;

	if (list->size_a > 1 && list->size_b > 1)
	{
		i = 0;
		tmp = list->a[i];
		i++;
		while (i < list->size_a)
		{
			list->a[i - 1] = list->a[i];
			i++;
		}
		list->a[i - 1] = tmp;
		i = 0;
		tmp = list->b[i];
		i++;
		while (i < list->size_b)
		{
			list->b[i - 1] = list->b[i];
			i++;
		}
		list->b[i - 1] = tmp;
		write(1, "rr\n", 3);
	}
}
