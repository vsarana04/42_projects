/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:12:21 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/11 14:13:39 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	max_bit(t_list *list)
{
	int	max;
	int	iter;
	int	i;

	i = 0;
	if (list->size_a == 0)
		return (0);
	max = list->a[0];
	iter = 0;
	while (i < list->size_a)
	{
		if (list->a[i] > max)
			max = list->a[i];
		i++;
	}
	while ((max >> iter) != 0)
		iter++;
	return (iter);
}

static void	radix_sort_stack_b(t_list *s, int b_size, int bit_size, int j)
{
	while (b_size-- && j <= bit_size && !is_sorted(s->a, s->size_a))
	{
		if (((s->b[0] >> j) & 1) == 0)
			rb(s);
		else
			pa(s);
	}
	if (is_sorted(s->a, s->size_a))
		while (s->size_b != 0)
			pa(s);
}

void	radix(t_list *list)
{
	int	i;
	int	bits;
	int	size;

	bits = max_bit(list);
	i = 0;
	while (i < bits)
	{
		size = list->size_a;
		while (size-- && !is_sorted(list->a, list->size_a))
		{
			if (((list->a[0] >> i) & 1) == 1)
				ra(list);
			else
				pb(list);
		}
		radix_sort_stack_b(list, list->size_b, bits, i + 1);
		i++;
	}
	while (list->size_b != 0)
		pa(list);
}
