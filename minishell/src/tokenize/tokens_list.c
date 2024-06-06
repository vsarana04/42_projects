/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:25:02 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/16 15:00:25 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*create_token(char *content)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = ft_strdup(content);
	if (!new_token->content)
	{
		free(new_token);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token **token_list, t_token *new_token)
{
	t_token	*tmp;

	if (!(*token_list))
		*token_list = new_token;
	else
	{
		tmp = *token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

void	finalize_word(t_shell *shell, t_token **tokens)
{
	if (shell->word_len > 0)
	{
		shell->current_word[shell->word_len] = '\0';
		add_token_to_list(tokens, create_token(shell->current_word));
		shell->word_len = 0;
	}
}
