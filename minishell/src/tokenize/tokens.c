/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:06:44 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/16 15:01:43 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenize(const char *input, t_shell *shell)
{
	t_token	*tokens;

	tokens = NULL;
	shell->i = 0;
	shell->word_len = 0;
	shell->current_word = malloc(sizeof(char) * 256);
	if (!shell->current_word)
		return (NULL);
	while (input[shell->i] != '\0')
	{
		if (!handle_character(input, &tokens, shell))
		{
			free(shell->current_word);
			free_tokens(tokens);
			return (NULL);
		}
	}
	finalize_word(shell, &tokens);
	free(shell->current_word);
	return (tokens);
}
