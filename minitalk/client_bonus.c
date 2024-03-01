/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:33:57 by vsarana           #+#    #+#             */
/*   Updated: 2023/08/24 13:14:23 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minitalk_bonus.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb *= 10;
		nb += str[i] - 48;
		i++;
	}
	nb *= sign;
	return (nb);
}

void	confirm(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("Success\n");
	else
		exit(0);
}

void	send_bit(int pid, char *c)
{
	int	bit;
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		bit = 0;
		while (bit < 8)
		{
			if ((c[i] >> bit) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(500);
			bit++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		signal(SIGUSR1, confirm);
		signal(SIGUSR2, confirm);
		send_bit(ft_atoi(argv[1]), argv[2]);
	}
	else
		ft_printf("Error\n");
	return (0);
}
