/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:06:37 by rukoltso          #+#    #+#             */
/*   Updated: 2024/05/16 20:16:34 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_pointers(void *ptr1, void *ptr2)
{
	free(ptr1);
	free(ptr2);
}

static int	change_directory_and_update_env(char *path, char *old_pwd,
		t_shell *shell)
{
	char	*new_pwd;

	update_env(&shell->env_list, "OLDPWD", old_pwd, shell);
	if (chdir(path) < 0)
	{
		perror("cd");
		free_pointers(path, old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd");
		free_pointers(path, old_pwd);
		return (1);
	}
	update_env(&shell->env_list, "PWD", new_pwd, shell);
	free_pointers(path, old_pwd);
	free(new_pwd);
	return (0);
}

static char	*get_path(char **words, t_shell *shell)
{
	char	*path;
	char	*home;

	if (words[1] == NULL || ft_strcmp(words[1], "~") == 0)
		path = ft_strdup(get_env(shell->env_list, "HOME"));
	else if (ft_strcmp(words[1], "-") == 0)
		path = ft_strdup(get_env(shell->env_list, "OLDPWD"));
	else if (words[1][0] == '~' && words[1][1] == '/')
	{
		home = get_env(shell->env_list, "HOME");
		path = ft_strjoin(home, words[1] + 1);
		free(home);
	}
	else
		path = ft_strdup(words[1]);
	return (path);
}

int	ms_cd(char **words, t_shell *shell)
{
	char	*path;
	char	*old_pwd;

	if (words[1] != NULL && words[2] != NULL)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (words[1] != NULL && (words[1][0] == '-' && words[1][1]))
		return (printf("Flags are not supported\n"), 1);
	path = get_path(words, shell);
	if (!path)
		return (perror("cd"), 1);
	old_pwd = ft_strdup(get_env(shell->env_list, "PWD"));
	if (change_directory_and_update_env(path, old_pwd, shell))
		return (1);
	return (0);
}

/* int	ms_cd(char **words, t_shell *shell)
{
	char	*path;
	char	*old_pwd;
	char	*home;

	path = NULL;
	if (words[1] != NULL && words[2] != NULL)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (words[1] != NULL && (words[1][0] == '-' && words[1][1]))
		return (printf("Flags are not supported\n"), 1);
	if (words[1] == NULL)
		path = ft_strdup(get_env(shell->env_list, "HOME"));
	else if (ft_strcmp(words[1], "~") == 0)
		path = ft_strdup(get_env(shell->env_list, "HOME"));
	else if (ft_strcmp(words[1], "-") == 0)
		path = ft_strdup(get_env(shell->env_list, "OLDPWD"));
	else if (words[1][0] == '~' && words[1][1] == '/')
	{
		home = get_env(shell->env_list, "HOME");
		path = ft_strjoin(home, words[1] + 1);
		free(home);
	}
	else
		path = ft_strdup(words[1]);
	if (!path)
		return (perror("cd"), 1);
	old_pwd = ft_strdup(get_env(shell->env_list, "PWD"));
	if (change_directory_and_update_env(path, old_pwd, shell))
		return (1);
	return (0);
} */
