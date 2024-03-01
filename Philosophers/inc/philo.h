/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:57:33 by vsarana           #+#    #+#             */
/*   Updated: 2023/11/21 13:20:49 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_config
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				philo_dead;
	int				simulation_end;
	long long int	start;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}		t_config;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				eating;
	long long int	last_meal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_config		*config;
}	t_philo;

long long	get_current_time(void);
void		init_data(t_config *config, char **av);
void		destroy(t_config *config, t_philo *philo);
void		*main_checker(void *pointer);
void		print_msg(t_philo *philo, char *msg);
void		ft_thinking(t_philo *philo);
void		ft_sleeping(t_philo *philo);
void		ft_eating(t_philo *philo);
int			init_thread(t_config *config);
int			is_number_valid(char *str);
int			validate_arg(char *arg, int max_value);
int			check_arguments(char **argv);
int			check_simulation_state(t_philo *philo);
int			ft_atoi(char *str);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *str);
int			ft_usleep(size_t condition);

#endif
