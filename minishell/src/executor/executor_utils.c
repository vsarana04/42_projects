/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:47:44 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/28 14:11:05 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_path_from_env_var(t_env_var *env_var)
{
	t_env_var	*current;

	current = env_var;
	while (current != NULL)
	{
		if (ft_strcmp(current->var_name, "PATH") == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

void	exec_cmd_path(t_data *commands, t_shell *shell, char *cmd_path)
{
	if (is_builtin(commands))
	{
		g_minishell = builtin(commands->full_cmd[0], commands->full_cmd, shell);
	}
	else if (cmd_path)
	{
		execute_command(commands, shell, cmd_path);
		free(cmd_path);
	}
	else
	{
		printf("Command not found: %s\n", commands->full_cmd[0]);
		g_minishell = 127;
	}
}

void	setup_redir(t_data *commands)
{
	commands->original_stdout = -1;
	commands->original_stdin = -1;
	if (commands->redirect_out)
	{
		commands->original_stdout = dup(STDOUT_FILENO);
		if (redirect_output(commands) == -1)
		{
			return ;
		}
	}
	if (commands->redirect_in || commands->use_heredoc)
	{
		commands->original_stdin = dup(STDIN_FILENO);
		if (commands->redirect_in && redirect_input(commands) == -1)
		{
			return ;
		}
	}
	if (commands->use_heredoc)
	{
		handle_here_doc(commands->heredoc_delimiter);
		commands->use_heredoc = 0;
	}
}

void	restore_redir(t_data *commands)
{
	if (commands->original_stdout != -1)
	{
		dup2(commands->original_stdout, STDOUT_FILENO);
		close(commands->original_stdout);
	}
	if (commands->original_stdin != -1)
	{
		dup2(commands->original_stdin, STDIN_FILENO);
		close(commands->original_stdin);
	}
}
