/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:50:11 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/16 15:27:45 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_escape(const char *input, t_shell *shell)
{
	if (input[shell->i + 1] == '\"' || input[shell->i + 1] == '\\')
	{
		shell->current_word[shell->word_len++] = input[shell->i + 1];
		shell->i++;
	}
	else
		shell->current_word[shell->word_len++] = input[shell->i];
}

static int	handle_double_quotes(const char *input, t_shell *shell)
{
	shell->i++;
	while (input[shell->i] != '\"' && input[shell->i] != '\0')
	{
		if (input[shell->i] == '\\')
			handle_escape(input, shell);
		else if (input[shell->i] == '$')
			shell->i = handle_dollar_sign(input, shell) - 1;
		else
			shell->current_word[shell->word_len++] = input[shell->i];
		shell->i++;
	}
	if (input[shell->i] == '\0')
	{
		write(1, "minishell: unclosed double quotes\n", 35);
		return (-1);
	}
	return (shell->i + 1);
}

static int	handle_single_quotes(const char *input, t_shell *shell)
{
	shell->i++;
	while (input[shell->i] != '\'' && input[shell->i] != '\0')
	{
		shell->current_word[shell->word_len++] = input[shell->i];
		shell->i++;
	}
	if (input[shell->i] == '\0')
	{
		write(1, "minishell: unclosed single quotes\n", 35);
		return (-1);
	}
	return (shell->i + 1);
}

int	handle_quotes(const char *input, t_shell *shell)
{
	if (input[shell->i] == '\"')
	{
		shell->i = handle_double_quotes(input, shell);
		if (shell->i == -1)
			return (0);
		shell->i++;
	}
	else if (input[shell->i] == '\'')
	{
		shell->i = handle_single_quotes(input, shell);
		if (shell->i == -1)
			return (0);
		shell->i++;
	}
	else if (input[shell->i] == '$')
	{
		shell->i = handle_dollar_sign(input, shell) - 1;
		shell->i++;
	}
	return (1);
}
