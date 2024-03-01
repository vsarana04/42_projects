/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:39:09 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/12 13:20:23 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static	int	find_index(int *sorted, int size, int num)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (sorted[i] == num)
			return (i);
		i++;
	}
	return (-1);
}

static void	bubble_sort(int *arr, int n)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	create_index(t_list *list)
{
	int	*temp;
	int	i;

	temp = (int *)malloc(list->size_a * sizeof(int));
	if (!temp)
		return ;
	i = 0;
	while (i < list->size_a)
	{
		temp[i] = list->a[i];
		i++;
	}
	bubble_sort(temp, list->size_a);
	i = 0;
	while (i < list->size_a)
	{
		list->a[i] = find_index(temp, list->size_a, list->a[i]);
		i++;
	}
	free(temp);
}
