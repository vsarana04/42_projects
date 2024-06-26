/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:27:22 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/27 16:55:41 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_process(t_data *command, char *cmd_path)
{
	int	in_fd;
	int	out_fd;

	in_fd = command->in_fd;
	out_fd = command->out_fd;
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	execve(cmd_path, command->full_cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

static void	parent_process(t_data *command, pid_t pid)
{
	int	status;
	int	in_fd;
	int	out_fd;

	in_fd = command->in_fd;
	out_fd = command->out_fd;
	waitpid(pid, &status, 0);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
}

static void	manage_process(t_data *command, int *pipe_fds, int has_next,
		char *path_var)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	if (pid == 0)
	{
		cmd_path = find_command_path(command->full_cmd[0], path_var);
		child_process(command, cmd_path);
	}
	else if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else
	{
		if (has_next)
			close(pipe_fds[1]);
		else
			parent_process(command, pid);
	}
}

static void	manage_pipes(t_data *commands, int *pipe_fds, int has_next)
{
	if (has_next)
	{
		if (pipe(pipe_fds) < 0)
		{
			perror("pipe");
			return ;
		}
		commands->out_fd = pipe_fds[1];
	}
	else
		commands->out_fd = STDOUT_FILENO;
}

void	exec_pipeline(t_data *commands, t_shell *shell)
{
	int	pipe_fds[2];
	int	has_next;
	int	in_fd;

	commands->in_fd = STDIN_FILENO;
	while (commands)
	{
		has_next = (commands->next != NULL);
		manage_pipes(commands, pipe_fds, has_next);
		manage_process(commands, pipe_fds, has_next, shell->path);
		in_fd = commands->in_fd;
		if (in_fd != STDIN_FILENO)
			close(in_fd);
		if (has_next)
			commands->next->in_fd = pipe_fds[0];
		else if (commands->next)
			commands->next->in_fd = STDIN_FILENO;
		commands = commands->next;
	}
}
