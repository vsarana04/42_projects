/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:02 by vsarana           #+#    #+#             */
/*   Updated: 2023/11/21 11:15:21 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_philos(t_config *config)
{
	int	i;

	i = 0;
	config->philo = malloc(sizeof(t_philo) * config->nb_philos);
	if (!config->philo)
		exit(1);
	while (i < config->nb_philos)
	{
		config->philo[i].id = i + 1;
		config->philo[i].eating = 0;
		config->philo[i].meals_eaten = 0;
		config->philo[i].last_meal = get_current_time();
		config->philo[i].l_fork = &config->forks[i];
		config->philo[i].r_fork = &config->forks[(i + 1) % config->nb_philos];
		config->philo[i].config = config;
		i++;
	}
}

static void	init_mutex(t_config *config)
{
	int	i;

	i = 0;
	config->forks = malloc(sizeof(pthread_mutex_t) * config->nb_philos);
	if (!config->forks)
		exit(1);
	while (i < config->nb_philos)
	{
		pthread_mutex_init(&config->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&config->write_mutex, NULL);
	config->start = get_current_time();
}

void	init_data(t_config *config, char **av)
{
	config->nb_philos = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		config->num_meals = ft_atoi(av[5]);
	else
		config->num_meals = -1;
	config->philo_dead = 0;
	config->simulation_end = 0;
	init_mutex(config);
	init_philos(config);
}
