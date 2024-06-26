/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_v1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:15:19 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/16 19:32:05 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**copy_env(char **envp)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (envp[i])
		i++;
	env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			while (i > 0)
				free(env_copy[--i]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

char	*get_path_var(char **envp)
{
	int		i;
	char	*path_var;

	i = 0;
	path_var = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_var = ft_strdup(envp[i] + 5);
			break ;
		}
		i++;
	}
	return (path_var);
}

void	update_shlvl(t_shell *shell)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = NULL;
	shlvl_str = get_env(shell->env_list, "SHLVL");
	if (shlvl_str == NULL)
		add_node(&shell->env_list, "SHLVL=1");
	else
	{
		shlvl = ft_atoi(shlvl_str);
		free(shlvl_str);
		shlvl_str = ft_itoa(shlvl + 1);
		update_env(&shell->env_list, "SHLVL", shlvl_str, shell);
		if (shlvl_str != NULL)
			free(shlvl_str);
	}
}

void	update_env_vars(t_shell *shell)
{
	if (shell->env_vars != NULL)
		free_str_array(shell->env_vars);
	shell->env_vars = env_list_to_array(shell->env_list);
}
