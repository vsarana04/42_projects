/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:15:41 by vsarana           #+#    #+#             */
/*   Updated: 2023/11/21 11:16:50 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy(t_config *config, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < config->nb_philos)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < config->nb_philos)
		pthread_mutex_destroy(&(config->forks[i]));
	pthread_mutex_destroy(&(config->write_mutex));
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *)philo_void;
	if ((philo->id % 2) == 0)
		ft_usleep(philo->config->time_to_eat / 2);
	while (!check_simulation_state(philo))
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (NULL);
}

int	init_thread(t_config *config)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = config->philo;
	while (i < config->nb_philos)
	{
		philo[i].last_meal = get_current_time();
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]))
		{
			destroy(config, philo);
			free(config->forks);
			free(config->philo);
			return (1);
		}
		i++;
	}
	main_checker(config->philo);
	destroy(config, philo);
	free(config->forks);
	free(config->philo);
	return (0);
}
