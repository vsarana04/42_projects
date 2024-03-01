/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:36:44 by vsarana           #+#    #+#             */
/*   Updated: 2023/11/20 17:38:49 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_thinking(t_philo *philo)
{
	print_msg(philo, "is thinking\n");
}

void	ft_sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping\n");
	ft_usleep(philo->config->time_to_sleep);
}

void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, "has taken a fork\n");
	if (philo->config->nb_philos == 1)
	{
		ft_usleep(philo->config->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, "has taken a fork\n");
	philo->eating = 1;
	print_msg(philo, "is eating\n");
	philo->last_meal = get_current_time();
	ft_usleep(philo->config->time_to_eat);
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}
