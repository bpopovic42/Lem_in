/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:50:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 16:14:57 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static int		remove_link(t_room *room, t_room *link)
{
	t_node	*links_ptr;
	t_room	*ptr;

	links_ptr = room->links->head;
	while (links_ptr)
	{
		ptr = *(t_room**)links_ptr->data;
		if (ptr == link)
		{
			ft_lstnode_remove(room->links, links_ptr);
			ft_node_del(&links_ptr, &free_room_ptr);
			return (1);
		}
		links_ptr = links_ptr->next;
	}
	return (0);
}

static int		has_alternative(t_room *room)
{
	t_node	*links_ptr;
	t_room	*ptr;

	links_ptr = room->links->head;
	while (links_ptr)
	{
		ptr = *(t_room**)links_ptr->data;
		if (ptr != room->to && ptr->end_distance >= 0)
			return (1);
		links_ptr = links_ptr->next;
	}
	return (0);

}

int		break_link(t_path *path)
{
	t_room	*ptr;
	int		alt;

	ptr = path->head;
	alt = 0;
	while (ptr->to && !room_is_end(ptr->to))
		ptr = ptr->to;
	while (ptr && !room_is_start(ptr))
	{
		if (!alt && room_has_multiple_links(ptr) && has_alternative(ptr))
			alt = 1;
		if (room_has_multiple_links(ptr) && !room_is_end_connected(ptr)
			&& !room_is_end(ptr) && !room_is_start(ptr) && alt)
		{
			print_dbg(1, "\nRemoving link %s->%s\n", ptr->name, ptr->to->name);
			remove_link(ptr, ptr->to);
			remove_link(ptr->to, ptr);
			return (1);
		}
		//alt = 0;
		ptr = ptr->from;
	}
	return (0);
}
