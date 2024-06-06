/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:49:45 by rukoltso          #+#    #+#             */
/*   Updated: 2024/01/22 12:58:26 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *s)
{
	long	i;
	long	nbr;
	long	isneg;

	i = 0;
	nbr = 0;
	isneg = 0;
	while (s[i] != '\0' && (s[i] == 32 || s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f'))
		i++;
	if (s[i] != '\0' && s[i] == '-')
	{
		isneg = 1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] != '\0' && ft_isdigit(s[i]))
		nbr = (nbr * 10) + (s[i++] - '0');
	if (isneg == 1)
		return (-nbr);
	return (nbr);
}
