/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:09:13 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/12 12:09:16 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	fill_list(t_list *list, char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		list->a[i] = ft_atoi_push(av[i], list);
		i++;
	}
	list->size_a = i;
}

static int	process_sign(char c, unsigned int *i)
{
	(*i)++;
	if (c == '-')
		return (-1);
	return (1);
}

int	ft_atoi_push(char *str, t_list *list)
{
	unsigned int	i;
	int				sign;
	long long int	number;

	i = 0;
	number = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign = process_sign(str[i], &i);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			free_memory(list, "Error\n");
		number = (str[i] - '0') + (number * 10);
		if (number > 2147483647 || (number * sign) < -2147483648 \
				|| ft_strlen(str) > 11)
			free_memory(list, "Error\n");
		i++;
	}
	return ((int)(number * sign));
}
