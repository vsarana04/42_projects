/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:17:10 by vsarana           #+#    #+#             */
/*   Updated: 2023/04/26 14:39:28 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (j);
}

static char	*ft_word_dup(const char *s, size_t len)
{
	char	*new;	

	new = (char *)malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, s, len);
	new[len] = '\0';
	return (new);
}

static	void	find_next_word(char const **s, char c, size_t *len)
{
	*len = 0;
	while (**s == c)
		(*s)++;
	while ((*s)[*len] && (*s)[*len] != c)
		(*len)++;
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	int		i;
	char	**result;

	i = 0;
	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!result)
		return (NULL);
	while (*s)
	{
		find_next_word(&s, c, &len);
		if (*s)
		{
			result[i++] = ft_word_dup(s, len);
			s += len;
		}
	}
	result[i] = NULL;
	return (result);
}
