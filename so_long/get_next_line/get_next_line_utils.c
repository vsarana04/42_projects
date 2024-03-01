/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:26:15 by vsarana           #+#    #+#             */
/*   Updated: 2023/09/11 19:26:18 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (src [i] != '\0' && i < (n - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strchr(const char *s, int c)
{
	while ((*s != (char)c))
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (0);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
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
