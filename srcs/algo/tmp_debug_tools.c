/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_debug_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:01:50 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/27 17:15:22 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path(t_path *path)
{
	t_dlist *ptr;

	if (path)
	{
		ptr = path->head;
		while (ptr)
		{
			ft_putendl((*((t_room**)ptr->content))->name);
			ptr = ptr->next;
		}
	}
}
