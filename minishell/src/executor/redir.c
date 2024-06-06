/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:54:30 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/28 13:59:47 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	write_error(const char *msg, const char *filename)
{
	write(2, msg, ft_strlen(msg));
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
}

int	redirect_output(t_data *data)
{
	int	fd;

	if (data->append)
		fd = open(data->out_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(data->out_path, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
	{
		write_error("Error opening file: ", data->out_path);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		write_error("Error with dup2 for file: ", data->out_path);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_input(t_data *data)
{
	int	fd;

	fd = open(data->in_path, O_RDONLY);
	if (fd == -1)
	{
		write_error("Error opening file: ", data->in_path);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		write_error("Error with dup2 for file: ", data->in_path);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	handle_here_doc(const char *delimiter)
{
	int		pipe_fds[2];
	char	*line;
	size_t	delimiter_len;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	delimiter_len = ft_strlen(delimiter);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (ft_strncmp(line, delimiter, delimiter_len) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fds[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
}
