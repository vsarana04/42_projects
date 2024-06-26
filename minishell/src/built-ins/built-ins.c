/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukoltso <rukoltso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:05:31 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/20 11:44:40 by rukoltso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(t_data *data)
{
	if (!data->full_cmd)
		return (0);
	if ((data->full_cmd && ft_strchr(*data->full_cmd, '/')) || (data->path
			&& ft_strchr(data->path, '/')))
		return (0);
	if (ft_strcmp(data->full_cmd[0], "echo") == 0)
		return (1);
	if (ft_strcmp(data->full_cmd[0], "exit") == 0)
		return (1);
	if (ft_strcmp(data->full_cmd[0], "cd") == 0)
		return (1);
	if (ft_strcmp(data->full_cmd[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(data->full_cmd[0], "env") == 0)
		return (1);
	if (ft_strcmp(data->full_cmd[0], "export") == 0)
		return (1);
	if (ft_strcmp(data->full_cmd[0], "unset") == 0)
		return (1);
	return (0);
}

int	builtin(char *cmd, char **args, t_shell *shell)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(cmd, "echo") == 0)
		ms_echo(args);
	if (ft_strcmp(cmd, "cd") == 0)
		ret = ms_cd(args, shell);
	if (ft_strcmp(cmd, "pwd") == 0)
		ret = ms_pwd();
	if (ft_strcmp(cmd, "env") == 0)
		ret = ms_env(shell->env_list);
	if (ft_strcmp(cmd, "exit") == 0)
		ret = ms_exit(shell, args);
	if (ft_strcmp(cmd, "unset") == 0)
		ret = ms_unset(&shell->env_list, args, shell);
	if (ft_strcmp(cmd, "export") == 0)
		ret = ms_export(&shell->env_list, args, shell);
	return (ret);
}
