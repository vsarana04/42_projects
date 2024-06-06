/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:58:34 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/16 19:46:32 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_commands(t_data *head)
{
	t_data	*tmp;
	int		i;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->full_cmd)
		{
			i = 0;
			while (tmp->full_cmd[i])
			{
				free(tmp->full_cmd[i]);
				i++;
			}
			free(tmp->full_cmd);
		}
		free(tmp->in_path);
		free(tmp->out_path);
		free(tmp);
	}
}

void	free_str_array(char **array)
{
	int	i;

	if (array != NULL)
	{
		i = 0;
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_env_list(t_env_var *env_list)
{
	t_env_var	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->var_name);
		free(tmp->content);
		free(tmp);
	}
}

void	free_shell(t_shell *shell)
{
	int	i;

	if (shell->env_vars)
	{
		i = 0;
		while (shell->env_vars[i])
		{
			free(shell->env_vars[i]);
			i++;
		}
		free(shell->env_vars);
	}
	free(shell->path);
	free(shell->cwd);
}
