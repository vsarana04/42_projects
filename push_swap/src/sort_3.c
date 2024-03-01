/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsarana <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:59:04 by vsarana           #+#    #+#             */
/*   Updated: 2023/10/11 14:00:15 by vsarana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

void	sort_3(t_list *list)
{	
	if (list->a[0] > list->a[1] && list->a[1] < list->a[2] \
			&& list->a[0] < list->a[2])
		sa(list);
	if (list->a[0] > list->a[1] && list->a[1] > list->a[2] \
			&& list->a[0] > list->a[2])
	{
		sa(list);
		rra(list);
	}
	if (list->a[0] > list->a[1] && list->a[1] < list->a[2] \
			&& list->a[0] > list->a[2])
		ra(list);
	if (list->a[0] < list->a[1] && list->a[0] > list->a[2] \
			&& list->a[1] > list->a[2])
		rra(list);
	if (list->a[0] < list->a[1] && list->a[1] > list->a[2] \
			&& list->a[0] < list->a[2])
	{
		sa(list);
		ra(list);
	}
}
