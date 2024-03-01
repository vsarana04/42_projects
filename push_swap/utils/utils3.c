/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:25:38 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/16 13:25:47 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	free_memory(t_list *list, char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	if (list)
	{
		if (list->a)
			free(list->a);
		if (list->b)
			free(list->b);
		free(list);
	}
	exit(1);
}

int	update_argc(char **av)
{
	int	new_argc;

	new_argc = 0;
	while (av[new_argc])
		new_argc++;
	return (new_argc);
}

char	**handle_single_arg(int *ac, char **av)
{
	if (*ac == 2 && (is_invalid_arg(*av)))
		free_memory(NULL, "Error\n");
	if (*ac == 2)
	{
		av = ft_split(*av, ' ');
		if (!av)
			free_memory(NULL, "Error\n");
		*ac = update_argc(av);
	}
	return (av);
}
