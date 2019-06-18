/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:52:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 17:46:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void		mark_next_room(t_room **from, t_room **next)
{
	print_dbg(0, "\t[Marking] %s->%s\n", (*from)->name, (*next)->name);
	(*from)->to = (*next);
	(*from)->blocked = 1;
	(*from)->cleaned = 0;
	if (!room_is_end((*next)))
	{
		(*next)->start_distance = (*from)->start_distance + 1;
		(*next)->from = (*from);
		(*from) = (*next);
	}
}

static int		link_is_shorter(t_room *src, t_room *link, t_room *shortest)
{
	if (link == src->from || room_is_start(link) || link->blocked)
		return (0);
	else if (link->end_distance >= 0)
	{
		if (shortest == NULL || shortest->end_distance > link->end_distance)
			return (1);
		else
			return (0);
	}
	return (0);
}

static t_room	*get_shortest_link(t_room *src)
{
	t_node	*link_ptr;
	t_room	*shortest;
	t_room	*link;

	link_ptr = src->links->head;
	shortest = NULL;
	link = NULL;
	while (link_ptr)
	{
		link = get_room_from_node(link_ptr);
		if (room_is_end(link))
			return (link);
		else if (link_is_shorter(src, link, shortest))
			shortest = link;
		link_ptr = link_ptr->next;
	}
	return (shortest);
}

static void		unmark_path(t_path *path, t_room *last_marked_room)
{
	t_room *ptr;
	t_room *previous;

	ptr = last_marked_room;
	while (ptr)
	{
		previous = ptr->from;
		ptr->blocked = 0;
		ptr->to = NULL;
		ptr->from = NULL;
		ptr = previous;
	}
	path->head->blocked = 1;
	path->length = -1;
}

void			mark_path(t_path *path)
{
	t_room	*ptr;
	t_room	*from;

	ptr = NULL;
	from = path->head;
	from->start_distance = 1;
	print_dbg(0, "Marking path %s :\n", from->name);
	while (!room_is_end(ptr) && (ptr = get_shortest_link(from)))
		mark_next_room(&from, &ptr);
	if ((from && room_is_end(ptr)) || (room_is_end(from) && !ptr))
	{
		print_dbg(2, "\tPath marked, length %d\n", from->start_distance);
		path_set_length(path, from->start_distance);
		if (!ptr)
			path->head->blocked = 1;
	}
	else
	{
		print_dbg(1, "\tFailed to mark path, cleaning.");
		unmark_path(path, from);
	}
}
