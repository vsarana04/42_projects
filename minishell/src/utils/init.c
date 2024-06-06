/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:05:24 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/15 14:37:23 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_env_list(t_shell *shell, char **envp)
{
	int			i;
	char		*env_var_copy;
	char		*name;
	char		*value;
	t_env_var	*new_node;

	i = 0;
	shell->env_list = NULL;
	while (envp[i] != NULL)
	{
		env_var_copy = ft_strdup(envp[i]);
		name = ft_strtok(env_var_copy, "=");
		value = ft_strtok(NULL, "=");
		if (name != NULL && value != NULL)
		{
			new_node = malloc(sizeof(t_env_var));
			new_node->var_name = ft_strdup(name);
			new_node->content = ft_strdup(value);
			new_node->next = shell->env_list;
			shell->env_list = new_node;
		}
		free(env_var_copy);
		i++;
	}
}

void	init_shell(t_shell *shell, char **envp)
{
	g_minishell = 0;
	shell->exit = false;
	shell->env_vars = copy_env(envp);
	shell->path = get_path_var(envp);
	shell->cwd = getcwd(NULL, 0);
	init_env_list(shell, envp);
	return ;
}
