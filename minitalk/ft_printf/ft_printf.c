/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:42:20 by vsarana           #+#    #+#             */
/*   Updated: 2023/05/16 18:04:30 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_checking(va_list args, const char format)
{
	int	cnt;

	cnt = 0;
	if (format == 'c')
		cnt += ft_putchar(va_arg(args, int));
	else if (format == 's')
		cnt += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		cnt += ft_putptr(va_arg(args, uintptr_t), format);
	else if (format == 'd' || format == 'i')
		cnt += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		cnt += ft_unsign_nbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		cnt += ft_puthex(va_arg(args, unsigned int), format);
	else if (format == '%')
		cnt += ft_putchar('%');
	return (cnt);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	va_start(args, format);
	while (format[i] != 0)
	{
		if (format[i] == '%')
		{
			cnt += ft_checking(args, format[i + 1]);
			i++;
		}
		else
			cnt += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (cnt);
}
