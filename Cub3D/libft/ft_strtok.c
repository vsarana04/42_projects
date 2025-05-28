/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:03:23 by rukoltso          #+#    #+#             */
/*   Updated: 2023/12/23 12:14:00 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char separrator)
{
	static char	*dup = NULL;
	char		*ptr;
	int			i;

	i = 0;
	ptr = NULL;
	if (str != NULL)
		dup = ft_strdup(str);
	while (*dup != '\0')
	{
		if (i == 0 && *dup != separrator)
		{
			i = 1;
			ptr = dup;
		}
		else if (i == 1 && *dup == separrator)
		{
			*dup = '\0';
			dup += 1;
			break ;
		}
		dup++;
	}
	return (ptr);
}
