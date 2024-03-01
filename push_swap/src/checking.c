/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:58:00 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/11 16:29:15 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int	is_sorted(int *array, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (array[i - 1] > array[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_invalid_arg(char *arg)
{
	int	i;

	i = 0;
	if (!arg || *arg == '\0')
		return (1);
	if (*arg == '-' || *arg == '+')
	{
		if (*(arg + 1) == '\0')
			return (1);
	}
	while (arg[i])
	{
		if (i == 0 && arg[i] == ' ' && arg[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	check_dup(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	while (i < list->size_a)
	{
		j = i + 1;
		while (j < list->size_a)
		{
			if (list->a[i] == list->a[j])
				free_memory(list, "Error\n");
			j++;
		}
		i++;
	}
}
