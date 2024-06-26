/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:35:00 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/28 14:38:08 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*parse_output_redirection(t_data *current_command, t_token *tokens)
{
	if (ft_strncmp(tokens->content, ">>", ft_strlen(">>")) == 0)
	{
		current_command->redirect_out = 1;
		current_command->append = 1;
		tokens = tokens->next;
		if (tokens != NULL && tokens->content != NULL)
			current_command->out_path = ft_strdup(tokens->content);
	}
	else if (ft_strncmp(tokens->content, ">", ft_strlen(">")) == 0)
	{
		current_command->redirect_out = 1;
		current_command->append = 0;
		tokens = tokens->next;
		if (tokens != NULL && tokens->content != NULL)
			current_command->out_path = ft_strdup(tokens->content);
	}
	return (tokens);
}

t_token	*parse_input_redirection(t_data *current_command, t_token *tokens)
{
	if (ft_strncmp(tokens->content, "<<", ft_strlen("<<")) == 0)
	{
		current_command->use_heredoc = 1;
		tokens = tokens->next;
		if (tokens != NULL && tokens->content != NULL)
			current_command->heredoc_delimiter = ft_strdup(tokens->content);
	}
	else if (ft_strncmp(tokens->content, "<", ft_strlen("<")) == 0)
	{
		current_command->redirect_in = 1;
		tokens = tokens->next;
		if (tokens != NULL && tokens->content != NULL)
			current_command->in_path = ft_strdup(tokens->content);
	}
	return (tokens);
}

t_token	*parse_redirection(t_data *current_command, t_token *tokens)
{
	tokens = parse_output_redirection(current_command, tokens);
	tokens = parse_input_redirection(current_command, tokens);
	return (tokens);
}
