/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:05:52 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/12 12:45:13 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static void	check_mode(t_list *list, int mode)
{
	if (mode == 1)
	{
		rra(list);
		pa(list);
		rra(list);
		rra(list);
	}
	else
	{
		ra(list);
		pa(list);
		sa(list);
		rra(list);
	}
}

void	stack_sorting(t_list *list, int mode)
{
	if (list->b[0] < list->a[0])
		pa(list);
	else if ((list->b[0] > list->a[0]) && (list->b[0] < list->a[1]))
	{
		ra(list);
		pa(list);
		rra(list);
	}
	else if ((list->b[0] > list->a[1]) && (list->b[0] < list->a[2]))
		check_mode(list, mode);
	else if (mode == 2 && (list->b[0] > list->a[2]) \
			&& (list->b[0] < list->a[3]))
	{
		rra(list);
		pa(list);
		ra(list);
		ra(list);
	}
	else
	{
		pa(list);
		ra(list);
	}
}

void	sort_5(t_list *list)
{
	int	nb;
	int	i;

	i = 0;
	if (list->size_a == 5)
		nb = 2;
	else
		nb = 1;
	while (i < nb)
	{
		pb(list);
		i++;
	}
	sort_3(list);
	while (list->size_b != 0)
	{
		if (list->size_a == 3)
			stack_sorting(list, 1);
		else if (list->size_a == 4)
			stack_sorting(list, 2);
	}
}
