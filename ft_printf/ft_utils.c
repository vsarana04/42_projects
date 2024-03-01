/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:48:50 by vsarana           #+#    #+#             */
/*   Updated: 2023/06/01 11:24:54 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long int	ft_int_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr <= 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static int	ft_unsigned_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_convert(char *str, unsigned int num, long int n)
{
	while (num != 0)
	{
		str[n--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	nb;
	long int		len;
	int				sign;

	len = ft_int_len(n);
	sign = 0;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[len--] = '\0';
	if (n == 0)
		result[0] = '0';
	if (n < 0)
	{
		sign = 1;
		nb = -n;
		result[0] = '-';
	}
	else
		nb = n;
	result = ft_convert(result, nb, len);
	return (result);
}

char	*ft_unsign_itoa(unsigned int n)
{
	char	*result;
	int		len;

	len = ft_unsigned_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len--] = '\0';
	if (n == 0)
		result[0] = '0';
	else
		result = ft_convert(result, n, len);
	return (result);
}
