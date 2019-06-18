/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_query_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:38:09 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 16:37:16 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		room_is_end(t_room *room)
{
	if (room && room->command && !ft_strcmp("##end", room->command))
		return (1);
	return (0);
}

int		room_is_start(t_room *room)
{
	if (room && room->command && !ft_strcmp("##start", room->command))
		return (1);
	return (0);
}

int		room_has_multiple_links(t_room *room)
{
	if (room && room->links && room->links->size > 2)
		return (1);
	return (0);
}

int		room_is_end_connected(t_room *room)
{
	t_room	*ptr;
	t_node	*links_ptr;

	if (room)
	{
		links_ptr = room->links->head;
		while (links_ptr)
		{
			ptr = *(t_room**)links_ptr->data;
			if (room_is_end(ptr))
				return (1);
			links_ptr = links_ptr->next;
		}
	}
	return (0);
}
