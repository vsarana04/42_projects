/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:44:21 by rukoltso          #+#    #+#             */
/*   Updated: 2023/02/08 10:18:09 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char const	*str;

	str = (unsigned char const *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char const)c)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
