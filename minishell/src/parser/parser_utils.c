/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:27:00 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/28 14:36:47 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	validate_command_exists_and_not_empty(t_data *commands)
{
	if (!commands)
	{
		write(2, "minishell: no command provided\n", 32);
		return (0);
	}
	if (!commands->full_cmd || !commands->full_cmd[0])
	{
		write(2, "minishell: empty command\n", 26);
		return (0);
	}
	return (1);
}

int	validate_command(t_data *commands)
{
	int		i;
	char	*last_arg;

	while (commands)
	{
		if (!validate_command_exists_and_not_empty(commands))
			return (0);
		if (!commands->full_cmd)
			return (0);
		i = 0;
		while (commands->full_cmd[i])
			i++;
		if (i == 0)
			return (0);
		last_arg = commands->full_cmd[i - 1];
		if (!last_arg || last_arg[ft_strlen(last_arg) - 1] == '|')
		{
			write(2, "minishell: incorrect use of pipes\n", 35);
			return (0);
		}
		commands = commands->next;
	}
	return (1);
}

int	is_redir_operator(char *token_content)
{
	if (ft_strncmp(token_content, ">>", ft_strlen(">>")) == 0
		|| ft_strncmp(token_content, "<<", ft_strlen("<<")) == 0
		|| ft_strncmp(token_content, ">", ft_strlen(">")) == 0
		|| ft_strncmp(token_content, "<", ft_strlen("<")) == 0)
	{
		return (1);
	}
	return (0);
}
