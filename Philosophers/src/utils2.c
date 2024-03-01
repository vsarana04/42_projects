/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:33:09 by vsarana           #+#    #+#             */
/*   Updated: 2023/11/21 11:46:37 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_number_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_arg(char *arg, int max_value)
{
	long long	value;

	if (!is_number_valid(arg))
		return (0);
	value = ft_atoi(arg);
	if (value <= 0 || value > max_value)
		return (0);
	return (1);
}

int	check_arguments(char **argv)
{
	if (!validate_arg(argv[2], INT_MAX))
	{
		printf("Check time_to_die!\n");
		return (1);
	}
	if (!validate_arg(argv[3], INT_MAX))
	{
		printf("Check time_to_eat!\n");
		return (1);
	}
	if (!validate_arg(argv[4], INT_MAX))
	{
		printf("Check time_to_sleep!\n");
		return (1);
	}
	if (argv[5] && !validate_arg(argv[5], INT_MAX))
	{
		printf("Check the number of meals!\n");
		return (1);
	}
	return (0);
}

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t condition)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < condition)
		usleep(500);
	return (0);
}
