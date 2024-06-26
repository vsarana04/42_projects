/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <vsarana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:11:58 by vsarana           #+#    #+#             */
/*   Updated: 2024/05/16 15:00:44 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_special_char(char c)
{
	int			result;
	const char	*special_chars;
	int			i;

	special_chars = "|&;(){}><";
	i = 0;
	result = 0;
	while (special_chars[i] != '\0')
	{
		if (c == special_chars[i])
		{
			result = 1;
			break ;
		}
		i++;
	}
	return (result);
}

int	is_valid_var_char(char c)
{
	int	result;

	result = 0;
	if (c >= 'A' && c <= 'Z')
		result = 1;
	else if (c >= 'a' && c <= 'z')
		result = 1;
	else if (c >= '0' && c <= '9')
		result = 1;
	else if (c == '_')
		result = 1;
	return (result);
}

char	*extract_var_name(const char *input)
{
	int		len;
	char	*var_name;

	len = 0;
	while (input[len] && is_valid_var_char(input[len]))
		len++;
	var_name = malloc(len + 1);
	if (var_name == NULL)
		return (NULL);
	ft_strlcpy(var_name, input, len + 1);
	return (var_name);
}
