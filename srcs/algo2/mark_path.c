/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:52:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 16:14:53 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_next_room(t_room **from, t_room **next)
{
	(*from)->to = (*next);
	(*from)->blocked = 1;
	if (!room_is_end((*next)))
	{
		(*next)->start_distance = (*from)->start_distance + 1;
		(*next)->from = (*from);
		(*from) = (*next); //
	}
}

#include "ft_printf.h"

int		link_is_shorter(t_room *src, t_room *link, t_room *shortest)
{
	ft_printf("for room %s link %s is ", src->name, link->name);
	if (link == src->from || room_is_start(link) || link->blocked)
	{
		if (link == src->from)
			ft_putendl("previous");
		else if (room_is_start(link))
			ft_putendl("start");
		else if (link->blocked)
			ft_putendl("blocked");
		return (0);
	}
	else if (link->end_distance >= 0)
	{
		if (shortest == NULL || shortest->end_distance > link->end_distance)
		{
			ft_putendl("valid");
			return (1);
		}
		else
		{
			ft_printf("longer than %s\n", shortest->name);
			return (0);
		}
	}
	ft_printf("unmarked (%d)\n", link->end_distance);
	return (0);
}

t_room	*get_shortest_link(t_room *src) //DIRTY
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
		if (room_is_end(link))//WUT
		{
			if (room_is_start(src) && link->blocked)
				return (NULL);
			return (link);
		}
		else if (link_is_shorter(src, link, shortest))
			shortest = link;
		link_ptr = link_ptr->next;
	}
	return (shortest);
}

void	mark_path(t_path *path)
{
	t_room	*ptr;
	t_room	*from;

	ptr = NULL;
	from = path->head;
	ft_putendl(from->name);
	from->start_distance = 1;
	while (!room_is_end(ptr) && (ptr = get_shortest_link(from))) //Might cause some issues
	{
		ft_putstr(from->name);
		ft_putchar(' ');
		mark_next_room(&from, &ptr);
	}
	ft_putchar('\n');
	if ((from && room_is_end(ptr)) || (room_is_end(from) && !ptr)) // if end is properly reached or start->end
	{
		path_set_final_length(path, from->start_distance);
		if (!ptr)
			path->head->blocked = 1; //UNSURE
	}
	else
		path->final_length = -1;
	path->head->blocked = 1; //UNSURE
}
