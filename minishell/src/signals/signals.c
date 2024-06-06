/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:04:16 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/14 14:06:26 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	new_prompt(int sig)
{
	(void)sig;
	g_minishell = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_minishell = 130;
	write(1, "\n", 1);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	g_minishell = 131;
	write(1, "quit (core dumped)\n", 20);
}

void	setup_signals(int sig)
{
	if (sig == 0)
	{
		signal(SIGINT, new_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
	}
}
