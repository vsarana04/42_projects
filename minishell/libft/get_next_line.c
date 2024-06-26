/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:31:16 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/22 13:56:07 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*empty_line(void)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = 0;
	return (str);
}

void	str_move(char **str, size_t start)
{
	char	*tmp;

	tmp = *str;
	*str = ft_substr(*str, start, ft_strlen(*str));
	free(tmp);
}

int	get_prev(char **prev, int fd)
{
	char	*buffer;
	ssize_t	rtn;

	if (!BUFFER_SIZE || BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (0);
	if (!(*prev))
		*prev = empty_line();
	if (!(*prev))
		return (0);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	rtn = read(fd, buffer, BUFFER_SIZE);
	while (rtn)
	{
		buffer[rtn] = 0;
		*prev = ft_strjoin(*prev, buffer);
		if (ft_charsrch(*prev, '\n') >= 0)
			break ;
		rtn = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	int			counter;
	static char	*prev = NULL;
	char		*str;

	if (!get_prev(&prev, fd))
		return (NULL);
	counter = ft_charsrch(prev, '\n');
	if (counter >= 0)
	{
		str = ft_substr(prev, 0, counter + 1);
		str_move(&prev, counter + 1);
	}
	else
	{
		str = ft_substr(prev, 0, ft_strlen(prev));
		free(prev);
		prev = NULL;
	}
	if (ft_strlen(str) == 0)
	{
		free(str);
		return (NULL);
	}
	return (str);
}
