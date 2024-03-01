/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:32:57 by vsarana           #+#    #+#             */
/*   Updated: 2023/05/16 18:07:40 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pointer(uintptr_t pointer, const char format, int *len)
{
	if (pointer >= 16)
	{
		ft_pointer(pointer / 16, format, len);
		ft_pointer(pointer % 16, format, len);
	}
	else
	{
		if (pointer <= 9)
			ft_putchar((pointer + '0'));
		else
		{
			if (format == 'p' || format == 'x')
				ft_putchar((pointer - 10 + 'a'));
			if (format == 'X')
				ft_putchar((pointer - 10 + 'A'));
		}
		(*len)++;
	}
}

int	ft_putptr(uintptr_t ptr, const char format)
{
	int	len;
	int	cnt;

	cnt = 0;
	len = 0;
	cnt += write(1, "0x", 2);
	if (!ptr)
		cnt += write(1, "0", 1);
	else
	{
		ft_pointer(ptr, format, &len);
		cnt += len;
	}
	return (cnt);
}

int	ft_puthex(uintptr_t ptr, const char format)
{
	int	len;
	int	cnt;

	cnt = 0;
	len = 0;
	if (!ptr)
		cnt += write(1, "0", 1);
	else
	{
		ft_pointer(ptr, format, &len);
		cnt += len;
	}
	return (cnt);
}
