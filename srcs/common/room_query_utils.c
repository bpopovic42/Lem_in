/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_query_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:38:09 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 16:39:33 by bopopovi         ###   ########.fr       */
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
	t_room	*link;
	t_node	*node;

	if (room)
	{
		node = room->links->head;
		while (node)
		{
			link = get_room_from_node(node);
			if (room_is_end(link))
				return (1);
			node = node->next;
		}
	}
	return (0);
}
