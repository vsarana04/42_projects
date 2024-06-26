/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:32:25 by vsarana           #+#    #+#             */
/*   Updated: 2024/03/28 16:29:16 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_fd(int fd, char *line, char *buffer)
{
	int		rl;
	char	*tmp;

	rl = 1;
	while (rl > 0)
	{
		rl = read(fd, buffer, BUFFER_SIZE);
		if (rl <= 0)
			break ;
		buffer[rl] = '\0';
		if (!line)
		{
			line = (char *)malloc(sizeof(char));
			if (!line)
				return (0);
			line[0] = '\0';
		}
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

static char	*ft_get(int fd, char *line)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = read_fd(fd, line, buffer);
	free(buffer);
	buffer = NULL;
	return (line);
}

static char	*ft_get_next_line(char *str)
{
	size_t	cnt;
	char	*line;

	cnt = 0;
	while (str[cnt] != '\n' && str[cnt] != '\0')
		cnt++;
	if (str[cnt] == '\0' || str[0] == '\0')
		return (0);
	line = ft_substr(str, cnt + 1, ft_strlen(str) - cnt);
	str[cnt + 1] = '\0';
	if (*line == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_get(fd, line);
	if (!str)
		return (NULL);
	line = ft_get_next_line(str);
	return (str);
}

#include <stdio.h>
#include <fcntl.h>


int main()
{
	int fd;
	char *line;
	


	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
