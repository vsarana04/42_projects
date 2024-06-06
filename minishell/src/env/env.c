/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:23:49 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/28 15:27:43 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_env_var	*create_env_var(char *env_var_str)
{
	t_env_var	*env_var;
	char		**vars;

	vars = ft_split(env_var_str, '=');
	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
		return (NULL);
	env_var->var_name = ft_strdup(vars[0]);
	if (vars[1] && vars[1][0] != '\0')
		env_var->content = ft_strdup(vars[1]);
	else
		env_var->content = NULL;
	if (!env_var->var_name || (vars[1] && !env_var->content))
	{
		free(env_var->content);
		free(env_var->var_name);
		free(env_var);
		return (NULL);
	}
	env_var->next = NULL;
	env_var->is_exported = true;
	free_array(vars);
	return (env_var);
}

t_env_var	*copy_env_to_struct(char **envp)
{
	t_env_var	*head;
	t_env_var	*prev;
	int			i;
	t_env_var	*new_node;

	head = NULL;
	prev = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = create_env_var(envp[i]);
		if (head == NULL)
			head = new_node;
		else
			prev->next = new_node;
		prev = new_node;
		i++;
	}
	return (head);
}

void	add_node(t_env_var **head, char *str)
{
	t_env_var	*new_node;
	t_env_var	*last;

	new_node = create_env_var(str);
	last = *head;
	if (new_node == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

int	is_node(char *str, t_env_var **head)
{
	t_env_var	*current;

	current = *head;
	while (current != NULL)
	{
		if (ft_strcmp(current->var_name, str) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}
