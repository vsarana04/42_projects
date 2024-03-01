/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:49:57 by vsarana           #+#    #+#             */
/*   Updated: 2023/05/03 17:27:10 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sublen;
	size_t	strcpy;
	char	*substr;

	if (!s)
		return (0);
	sublen = ft_strlen(s);
	strcpy = 0;
	if (start >= sublen)
	{	
		substr = (char *)malloc(sizeof(char));
		if (!substr)
			return (0);
		substr[0] = '\0';
		return (substr);
	}
	strcpy = sublen - start;
	if (strcpy > len)
		strcpy = len;
	substr = (char *)malloc(sizeof(char) * (strcpy + 1));
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, strcpy + 1);
	return (substr);
}
