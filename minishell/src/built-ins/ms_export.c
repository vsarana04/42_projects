/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:11:40 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/28 14:01:41 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_dup(t_env_var *env, char *str)
{
	while (env)
	{
		if (ft_strcmp(env->var_name, str) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

static void	check_args(t_env_var **env, char **args, t_shell *shell)
{
	char	*var_name;
	char	*value;

	var_name = ft_strtok(args[1], "=");
	value = ft_strtok(NULL, "=");
	if (check_dup(*env, var_name))
	{
		if (value != NULL)
			update_env(env, var_name, value, shell);
	}
	else
	{
		if (check_export(var_name))
			create_env(env, var_name, value, shell);
		else
			printf("export: '%s': not a valid identifier\n", var_name);
	}
}

int	ms_export(t_env_var **env, char **args, t_shell *shell)
{
	if (args[1] == NULL)
	{
		ms_env(*env);
		return (0);
	}
	else
		check_args(env, args, shell);
	return (0);
}
