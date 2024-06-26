/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:26:55 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/28 14:11:10 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_command_path(char *cmd, char *path_var)
{
	char	**paths;
	char	*cmd_path;
	int		i;
	char	*slash_cmd;

	cmd_path = NULL;
	i = 0;
	paths = ft_split(path_var, ':');
	while (paths[i])
	{
		slash_cmd = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(paths[i], slash_cmd);
		free(slash_cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free_str_array(paths);
			return (cmd_path);
		}
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

void	execute_command(t_data *commands, t_shell *shell, char *cmd_path)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, commands->full_cmd, shell->env_vars);
		free(cmd_path);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		g_minishell = EXIT_FAILURE;
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_minishell = WEXITSTATUS(status);
	}
}

char	*exec_binary(char *cmd, char *path_var)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	else
		return (find_command_path(cmd, path_var));
}

void	exec_command(t_data *commands, t_shell *shell)
{
	char	*cmd_path;
	char	*path_var;

	if (!commands->full_cmd || !commands->full_cmd[0])
		return ;
	setup_redir(commands);
	path_var = get_path_from_env_var(shell->env_list);
	if (path_var == NULL)
	{
		printf("Error: PATH variable not set\n");
		return ;
	}
	cmd_path = exec_binary(commands->full_cmd[0], shell->path);
	exec_cmd_path(commands, shell, cmd_path);
	restore_redir(commands);
}

void	executor(t_data *commands, t_shell *shell)
{
	if (!commands)
		return ;
	setup_signals(1);
	if (commands->next)
		exec_pipeline(commands, shell);
	else
		exec_command(commands, shell);
}
