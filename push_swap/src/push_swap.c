/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:05:17 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/16 13:20:30 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	sorting(t_list *list)
{
	if (list->size_a == 2 && list->a[0] > list->a[1])
		sa(list);
	else if (list->size_a == 3)
		sort_3(list);
	else if (list->size_a >= 4 && list->size_a <= 5)
		sort_5(list);
	else
		radix(list);
	return (0);
}

t_list	*init_list(int size)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->a = (int *)malloc(sizeof(int) * size);
	list->b = (int *)malloc(sizeof(int) * size);
	if (!list->a || !list->a)
	{
		free_memory(list, "Error\n");
		return (NULL);
	}
	list->size_a = size;
	list->size_b = 0;
	return (list);
}

int	main(int ac, char **av)
{
	t_list	*list;

	if (ac < 2)
		return (0);
	av++;
	av = handle_single_arg(&ac, av);
	list = init_list(ac);
	fill_list(list, av);
	check_dup(list);
	create_index(list);
	if (is_sorted(list->a, list->size_a))
	{
		free_memory(list, NULL);
		return (1);
	}
	sorting(list);
	free_memory(list, NULL);
	return (0);
}
