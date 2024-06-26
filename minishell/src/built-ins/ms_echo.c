/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:29 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/16 19:20:53 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern int	g_minishell;

static int	echo_check(char *str)
{
	if (ft_strncmp(str, "-n", 2) == 0)
		return (1);
	return (0);
}

static void	exit_status(char *word)
{
	char	*ret;

	if (ft_strcmp(word, "$?") == 0)
	{
		ret = ft_itoa(g_minishell);
		ft_putstr_fd(ret, 1);
		free(ret);
	}
	else
		ft_putstr_fd(word, 1);
}

void	ms_echo(char **words)
{
	int		i;
	bool	flags;
	bool	flag_found;

	i = 1;
	flags = false;
	flag_found = false;
	while (words[i])
	{
		if (echo_check(words[i]) == 1 && !flags)
			flag_found = true;
		else
		{
			flags = true;
			exit_status(words[i]);
			if (words[i + 1] && words[i][0] != '\0')
				ft_putstr_fd(" ", 1);
		}
		i++;
	}
	if (!flag_found)
		ft_putstr_fd("\n", 1);
}
