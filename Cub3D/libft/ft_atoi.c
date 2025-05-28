/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 22:23:08 by rukoltso          #+#    #+#             */
/*   Updated: 2024/11/28 13:34:12 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	nbr;
	int	isneg;

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
