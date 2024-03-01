/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:42:00 by vsarana           #+#    #+#             */
/*   Updated: 2023/04/25 11:29:54 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nb, size_t size)
{
	void	*arr;

	arr = (void *)malloc(nb * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (nb * size));
	return (arr);
}
