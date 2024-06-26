/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:14:21 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/14 13:14:42 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_unset(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (printf("unset: not an identifier: %s\n", str), 0);
	while (str[i])
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (printf("unset: not an identifier: %s\n", str), 0);
		i++;
	}
	return (1);
}

int	ms_unset(t_env_var **env, char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		return (printf("unset: not enough arguments\n"), 1);
	else
	{
		while (args[i])
		{
			if (check_unset(args[i]))
				delete_env(env, args[i], shell);
			else
				return (printf("unset: %s: invalid identifier\n", args[i]), 1);
			i++;
		}
	}
	return (0);
}
