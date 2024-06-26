/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_v3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:31:01 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/28 14:19:37 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_env_list(t_env_var *env_list)
{
	int			count;
	t_env_var	*tmp;

	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	init_env_array(char **env_array, int count)
{
	int	i;

	i = 0;
	while (i <= count)
	{
		env_array[i] = NULL;
		i++;
	}
}

static void	fill_env_array(char **env_array, t_env_var *env_list)
{
	t_env_var	*tmp;
	char		*temp;
	int			i;

	tmp = env_list;
	i = 0;
	while (tmp)
	{
		if (tmp->content && tmp->content[0] != '\0')
		{
			temp = ft_strjoin(tmp->var_name, "=");
			env_array[i] = ft_strjoin(temp, tmp->content);
			free(temp);
		}
		else
			env_array[i] = ft_strdup(tmp->var_name);
		tmp = tmp->next;
		i++;
	}
}

char	**env_list_to_array(t_env_var *env_list)
{
	int		count;
	char	**env_array;

	count = count_env_list(env_list);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	init_env_array(env_array, count);
	fill_env_array(env_array, env_list);
	return (env_array);
}
