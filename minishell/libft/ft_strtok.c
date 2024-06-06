/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:03:23 by rukoltso          #+#    #+#             */
/*   Updated: 2023/12/23 12:45:08 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *sep)
{
	static char	*next_token = NULL;
	char		*token;

	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	while (*next_token != '\0' && ft_strchr(sep, *next_token) != NULL)
		next_token++;
	if (*next_token == '\0')
	{
		next_token = NULL;
		return (NULL);
	}
	token = next_token;
	while (*next_token != '\0' && ft_strchr(sep, *next_token) == NULL)
		next_token++;
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}
	return (token);
}
