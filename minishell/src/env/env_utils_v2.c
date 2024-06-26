/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:20:36 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/28 14:18:50 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env(t_env_var *head, char *var_name)
{
	t_env_var	*current;

	if (var_name == NULL)
		return (NULL);
	current = head;
	while (current != NULL)
	{
		if (current->var_name != NULL && ft_strcmp(var_name,
				current->var_name) == 0)
		{
			if (current->content == NULL)
				return (NULL);
			return (ft_strdup(current->content));
		}
		current = current->next;
	}
	return (NULL);
}

void	update_env(t_env_var **head, char *var_name, char *new_content,
		t_shell *shell)
{
	t_env_var	*current;
	char		*new_var;

	current = *head;
	while (current != NULL)
	{
		if (ft_strcmp(var_name, current->var_name) == 0)
		{
			free(current->content);
			current->content = ft_strdup(new_content);
			update_env_vars(shell);
			return ;
		}
		current = current->next;
	}
	new_var = malloc(ft_strlen(var_name) + ft_strlen(new_content) + 2);
	ft_strlcpy(new_var, var_name, ft_strlen(var_name) + 1);
	ft_strlcat(new_var, "=", 2);
	ft_strlcat(new_var, new_content, ft_strlen(new_content) + 1);
	add_node(head, new_var);
	free(new_var);
	update_env_vars(shell);
}

void	create_new_env(t_env_var **head, char *var_name, char *content,
		t_shell *shell)
{
	int		var_length;
	char	*new_var;

	var_length = ft_strlen(var_name) + 1;
	if (content && content[0] != '\0')
		var_length += ft_strlen(content) + 1;
	new_var = malloc(var_length);
	ft_strcpy(new_var, var_name);
	if (content && content[0] != '\0')
	{
		ft_strcat(new_var, "=");
		ft_strcat(new_var, content);
	}
	add_node(head, new_var);
	free(new_var);
	update_env_vars(shell);
}

void	create_env(t_env_var **head, char *var_name, char *content,
		t_shell *shell)
{
	char	*existing_env;

	existing_env = get_env(*head, var_name);
	if (existing_env != NULL)
	{
		update_env(head, var_name, content, shell);
		free(existing_env);
	}
	else
	{
		create_new_env(head, var_name, content, shell);
	}
}

void	delete_env(t_env_var **head, char *var_name, t_shell *shell)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(var_name, current->var_name) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->var_name);
			free(current->content);
			free(current);
			update_env_vars(shell);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
