/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:44:53 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/12 15:30:52 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	pa(t_list *list)
{
	int	i;

	if (list->size_b)
	{
		i = list->size_a++;
		while (i > 0)
		{
			list->a[i] = list->a[i - 1];
			i--;
		}
		list->a[0] = list->b[0];
		i = 0;
		list->size_b--;
		while (i < list->size_b)
		{
			list->b[i] = list->b[i + 1];
			i++;
		}
		write(1, "pa\n", 3);
	}
}

void	pb(t_list *list)
{
	int	i;

	if (list->size_a)
	{
		i = list->size_b++;
		while (i > 0)
		{
			list->b[i] = list->b[i - 1];
			i--;
		}
		list->b[0] = list->a[0];
		i = 0;
		list->size_a--;
		while (i < list->size_a)
		{
			list->a[i] = list->a[i + 1];
			i++;
		}
		write(1, "pb\n", 3);
	}
}
