/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:39:03 by vsarana           #+#    #+#             */
/*   Updated: 2023/11/21 11:14:23 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_simulation_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->write_mutex);
	if (philo->config->philo_dead || philo->config->simulation_end)
	{
		pthread_mutex_unlock(&philo->config->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->config->write_mutex);
	return (0);
}

int	check_philo_death(t_philo *philo)
{
	long long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->config->write_mutex);
	if ((current_time - philo->last_meal >= philo->config->time_to_die)
		&& !philo->eating)
	{
		pthread_mutex_unlock(&philo->config->write_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->config->write_mutex);
	return (0);
}

int	check_philos_status(t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < philo->config->nb_philos)
	{
		if (check_philo_death(&philo[i]))
		{
			print_msg(&philo[i], "died\n");
			return (philo->config->philo_dead = 1);
		}
		if (philo->config->num_meals != -1
			&& philo[i].meals_eaten >= philo->config->num_meals)
			j++;
		i++;
	}
	return (j == philo->config->nb_philos);
}

void	*main_checker(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (!philo->config->simulation_end)
	{
		if (check_philos_status(philo))
		{
			philo->config->simulation_end = 1;
			break ;
		}
	}
	return (NULL);
}
