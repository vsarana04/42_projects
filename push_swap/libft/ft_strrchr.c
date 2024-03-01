/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:17:26 by vsarana           #+#    #+#             */
/*   Updated: 2023/05/03 17:59:35 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == 0 && s[i] == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if ((char)s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
