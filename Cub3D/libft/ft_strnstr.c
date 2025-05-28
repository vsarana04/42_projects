/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:14:15 by rukoltso          #+#    #+#             */
/*   Updated: 2023/01/25 22:45:16 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && k < len)
	{
		while (big[i] && big[i] == little[j] && (k + i) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i - j);
			j++;
			i++;
		}
		i = 0;
		j = 0;
		big++;
		k++;
	}
	return (NULL);
}
