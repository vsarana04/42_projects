/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:55:29 by vsarana           #+#    #+#             */
/*   Updated: 2023/11/21 11:56:42 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if ((argc != 5 && argc != 6) || check_arguments(argv))
	{
		printf("Check your arguments!\n");
		return (1);
	}
	init_data(&config, argv);
	init_thread(&config);
	return (0);
}
