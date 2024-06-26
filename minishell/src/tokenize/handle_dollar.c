/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:41:20 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/16 14:59:42 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*resolve_variable_value(const char *input, t_shell *shell)
{
	char	*var_value;
	char	*var_name;

	if (input[shell->i + 1] == '?')
	{
		var_value = ft_itoa(g_minishell);
		shell->i += 2;
	}
	else
	{
		var_name = extract_var_name(input + shell->i + 1);
		var_value = get_env(shell->env_list, var_name);
		shell->i += ft_strlen(var_name) + 1;
		free(var_name);
	}
	return (var_value);
}

static int	update_current_word(t_shell *shell, char *var_value)
{
	size_t	new_size;
	char	*new_word;

	new_size = shell->word_len + ft_strlen(var_value);
	new_word = malloc(new_size + 1);
	if (!new_word)
	{
		perror("Memory allocation failed");
		free(shell->current_word);
		return (-1);
	}
	ft_strlcpy(new_word, shell->current_word, shell->word_len + 1);
	ft_strlcpy(new_word + shell->word_len, var_value, ft_strlen(var_value) + 1);
	free(shell->current_word);
	shell->current_word = new_word;
	shell->word_len = new_size;
	return (0);
}

int	handle_dollar_sign(const char *input, t_shell *shell)
{
	char	*var_value;

	var_value = resolve_variable_value(input, shell);
	if (!var_value)
		return (shell->i);
	if (update_current_word(shell, var_value) == -1)
	{
		free(var_value);
		return (-1);
	}
	if (input[shell->i] != '?' || input[shell->i - 1] != '$')
		free(var_value);
	return (shell->i);
}
