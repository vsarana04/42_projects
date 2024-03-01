/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:47:30 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/12 15:34:10 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	sa(t_list *list)
{
	int	tmp;

	tmp = 0;
	if (list->size_a > 1)
	{		
		tmp = list->a[0];
		list->a[0] = list->a[1];
		list->a[1] = tmp;
	}
	write(1, "sa\n", 3);
}

void	sb(t_list *list)
{
	int	tmp;

	tmp = 0;
	if (list->size_b > 1)
	{
		tmp = list->b[0];
		list->b[0] = list->b[1];
		list->b[1] = tmp;
	}
	write(1, "sb\n", 3);
}

void	ss(t_list *list)
{
	int	tmp;

	tmp = 0;
	if (list->size_a >= 2 && list->size_b >= 2)
	{
		tmp = list->a[0];
		list->a[0] = list->a[1];
		list->a[1] = tmp;
		tmp = list->b[0];
		list->b[0] = list->b[1];
		list->b[1] = tmp;
	}
	write(1, "ss\n", 3);
}
