/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:32:12 by vsarana           #+#    #+#             */
/*   Updated: 2023/04/24 17:09:35 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *f, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (f == s || f[0] == '\0')
		return ((char *)s);
	while (s[i] != '\0' && i < n)
	{
		j = 0;
		while (s[i + j] == f[j] && i + j < n)
		{
			if (f[j + 1] == '\0')
				return ((char *)s + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
