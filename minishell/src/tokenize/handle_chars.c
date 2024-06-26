/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:27:38 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/16 14:58:57 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_special_chars(const char *input, t_shell *shell,
		t_token **tokens)
{
	int		length;
	char	special[3];

	length = 1;
	special[0] = 0;
	special[1] = 0;
	special[2] = 0;
	if (shell->word_len > 0)
		finalize_word(shell, tokens);
	special[0] = input[shell->i];
	if ((input[shell->i] == '<' && input[shell->i + 1] == '<')
		|| (input[shell->i] == '>' && input[shell->i + 1] == '>'))
	{
		special[1] = input[shell->i + 1];
		length++;
		shell->i++;
	}
	add_token_to_list(tokens, create_token(special));
	shell->i++;
}

static void	handle_escapes(const char *input, t_shell *shell)
{
	shell->i++;
	if (input[shell->i] == 'n')
		shell->current_word[shell->word_len++] = '\n';
	else if (input[shell->i] == 't')
		shell->current_word[shell->word_len++] = '\t';
	else
		shell->current_word[shell->word_len++] = input[shell->i];
	shell->i++;
}

int	handle_character(const char *input, t_token **tokens, t_shell *shell)
{
	if (input[shell->i] == '\"' || input[shell->i] == '\''
		|| input[shell->i] == '$')
	{
		if (!handle_quotes(input, shell))
			return (0);
	}
	else if (input[shell->i] == '\\')
	{
		handle_escapes(input, shell);
		shell->i++;
	}
	else if (is_special_char(input[shell->i]))
		handle_special_chars(input, shell, tokens);
	else if (input[shell->i] == ' ')
	{
		finalize_word(shell, tokens);
		shell->i++;
	}
	else
	{
		shell->current_word[shell->word_len++] = input[shell->i];
		shell->i++;
	}
	return (1);
}
