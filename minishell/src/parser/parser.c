/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:05:36 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/28 15:43:52 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_data	*initialize_command(void)
{
	t_data	*cmd;

	cmd = malloc(sizeof(t_data));
	if (!cmd)
	{
		perror("Memory error");
		exit(ERROR);
	}
	cmd->full_cmd = NULL;
	cmd->path = NULL;
	cmd->in_fd = 0;
	cmd->out_fd = 0;
	cmd->redirect_in = 0;
	cmd->redirect_out = 0;
	cmd->append = 0;
	cmd->in_path = NULL;
	cmd->out_path = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_data	*create_command(char **args, int arg_cnt)
{
	t_data	*cmd;
	int		i;

	i = 0;
	cmd = initialize_command();
	cmd->full_cmd = malloc(sizeof(char *) * (arg_cnt + 1));
	if (!cmd->full_cmd)
	{
		perror("Memory error");
		exit(ERROR);
	}
	while (i < arg_cnt)
	{
		cmd->full_cmd[i] = args[i];
		i++;
	}
	cmd->full_cmd[arg_cnt] = NULL;
	return (cmd);
}

t_data	*add_command(t_data **head, t_data **current_command, char *args[],
		int arg_cnt)
{
	if (!*head)
	{
		*current_command = create_command(args, arg_cnt);
		*head = *current_command;
	}
	else
	{
		(*current_command)->next = create_command(args, arg_cnt);
		(*current_command) = (*current_command)->next;
	}
	if (!validate_command(*current_command))
	{
		printf("Syntax error in command structure.\n");
		free_commands(*head);
		return (NULL);
	}
	return (*head);
}

t_data	*parse_tokens(t_token *tokens, t_data *head, t_data *current_command,
		int arg_cnt)
{
	char	*args[1024];

	while (tokens)
	{
		if (ft_strncmp(tokens->content, "|", ft_strlen("|")) == 0)
		{
			head = add_command(&head, &current_command, args, arg_cnt);
			arg_cnt = 0;
		}
		else if (is_redir_operator(tokens->content))
		{
			if (current_command == NULL)
			{
				head = add_command(&head, &current_command, args, arg_cnt);
				arg_cnt = 0;
			}
			tokens = parse_redirection(current_command, tokens);
		}
		else if (tokens->content)
			args[arg_cnt++] = ft_strdup(tokens->content);
		tokens = tokens->next;
	}
	if (arg_cnt > 0)
		head = add_command(&head, &current_command, args, arg_cnt);
	return (head);
}
