/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:05:03 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/28 15:38:57 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_minishell;

void	handle_input(t_shell *shell, char *input)
{
	t_token	*tokens;
	t_data	*parsed_cmds;

	if (*input)
	{
		add_history(input);
		tokens = tokenize(input, shell);
		parsed_cmds = parse_tokens(tokens, NULL, NULL, 0);
		executor(parsed_cmds, shell);
		free_tokens(tokens);
		free_commands(parsed_cmds);
	}
	free(input);
}

void	minishell(t_shell *shell)
{
	char	*input;

	update_shlvl(shell);
	while (shell->exit == false)
	{
		setup_signals(0);
		input = readline("minishell> ");
		if (!input)
		{
			write(1, "exit\n", 6);
			shell->exit = true;
			continue ;
		}
		handle_input(shell, input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	if (argc > 1)
	{
		write(1, "minishell: Usage: ./Minishell\n", 31);
		return (1);
	}
	init_shell(&shell, envp);
	minishell(&shell);
	free_shell(&shell);
	free_env_list(shell.env_list);
	return (g_minishell);
}
