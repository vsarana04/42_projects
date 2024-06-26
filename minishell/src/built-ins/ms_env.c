/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:08:54 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/28 14:01:26 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_env(t_env_var *env)
{
	if (!env)
		return (1);
	while (env)
	{
		if (env->content != NULL || env->is_exported)
		{
			printf("%s", env->var_name);
			if (env->content)
				printf("=%s", env->content);
			printf("\n");
		}
		env = env->next;
	}
	return (0);
}
