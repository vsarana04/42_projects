/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:49:33 by vsarana           #+#    #+#             */
/*   Updated: 2023/06/01 11:26:14 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		cnt;
	char	*str;

	cnt = 0;
	str = ft_itoa(n);
	cnt += ft_putstr(str);
	free(str);
	return (cnt);
}

int	ft_unsign_nbr(unsigned int n)
{
	int		cnt;
	char	*str;

	cnt = 0;
	str = ft_unsign_itoa(n);
	cnt += ft_putstr(str);
	free(str);
	return (cnt);
}
