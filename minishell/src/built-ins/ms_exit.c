/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:10:32 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/20 11:46:36 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	ret_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ms_exit(t_shell *shell, char **prompt)
{
	bool	binary;

	shell->exit = true;
	ft_putendl_fd("exit", 2);
	if (prompt[1] && prompt[2])
	{
		ft_putendl_fd("minishell> too many arguments", 2);
		shell->ret = 1;
	}
	else if (prompt[1])
	{
		binary = ret_is_num(prompt[1]);
		if (!binary)
		{
			shell->ret = 2;
			ft_putstr_fd("minishell> exit: ", 2);
			ft_putstr_fd(prompt[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
		}
		else
			shell->ret = ft_atoi(prompt[1]);
	}
	else
		shell->ret = 0;
	return (shell->ret);
}
