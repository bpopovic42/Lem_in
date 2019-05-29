/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:06:07 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/29 21:15:17 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	local_exit(char **rooms, int return_value)
{
	if (rooms)
		ft_delarray(rooms);
	return (return_value);
}

static int	record_link(t_graph *graph, char *room_a, char *room_b)
{
	t_room *ptr_a;
	t_room *ptr_b;

	ptr_a = ft_hashget_data(graph->rooms, room_a);
	ptr_b = ft_hashget_data(graph->rooms, room_b);
	return (link_add(graph, ptr_a, ptr_b));
}

static int	link_exists(t_graph *graph, char *room_a, char *room_b)
{
	t_room	*room_a_ptr;
	t_room	*room_b_ptr;

	room_a_ptr = ft_hashget_data(graph->rooms, room_a);
	room_b_ptr = ft_hashget_data(graph->rooms, room_b);
	if (room_a_ptr->links && room_a_ptr->links->size > 0)
		return (room_has_link(room_a_ptr, room_b_ptr));
	return (0);
}

static int	room_exists(t_graph *graph, char *room)
{
	if (graph->nbr_of_rooms && ft_hashget_data(graph->rooms, room))
		return (1);
	return (0);
}

int			parse_link(t_graph *graph, const char *link)
{
	char	**rooms;

	rooms = NULL;
	if (!(rooms = ft_strsplit(link, "-")))
		return (local_exit(rooms, -1));
	if (!ft_strcmp(rooms[0], rooms[1]))
		return (local_exit(rooms, 1));
	else if (!room_exists(graph, rooms[0]) || !room_exists(graph, rooms[1]))
		return (local_exit(rooms, 1));
	else if (link_exists(graph, rooms[0], rooms[1]))
		return (local_exit(rooms, 1));
	if (record_link(graph, rooms[0], rooms[1]) < 0)
		return (local_exit(rooms, -1));
	return (local_exit(rooms, 0));
}
