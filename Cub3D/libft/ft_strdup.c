/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 22:20:23 by rukoltso          #+#    #+#             */
/*   Updated: 2023/02/08 14:18:15 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*mem;
	int		i;

	len = ft_strlen(s) + 1;
	mem = (char *)malloc(sizeof(char) * len);
	if (!mem)
		return (NULL);
	i = 0;
	mem = ft_memcpy(mem, s, len);
	while (mem[i])
	{
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
