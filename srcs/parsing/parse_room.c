/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/22 20:38:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		local_exit(char **room_data, int retval)
{
	if (room_data)
		ft_delarray(room_data);
	return (retval);
}

static void		update_graph_data(t_graph *graph, t_room *room)
{
	if (graph->last_command)
		room->command = graph->last_command;
	if (room_is_start(room))
		graph->start = room;
	else if (room_is_end(room))
		graph->end = room;
	graph->last_command = NULL;
	graph->nbr_of_rooms++;
}

static int		record_room(t_graph *graph, t_room *room)
{
	if (!room_has_conflict(graph, room))
	{
		if (ft_vector_append(graph->room_list, (void**)&room) < 0)
			return (-1);
		if (ft_hashpush_data(graph->rooms, room->name, room, sizeof(*room)) < 0)
			return (-1);
		update_graph_data(graph, room);
		return (0);
	}
	return (1);
}

int				parse_room(t_graph *graph, const char *line)
{
	t_room	*room;
	int		error_status;
	char	**room_data;

	room = NULL;
	error_status = 0;
	if (!(room_data = ft_strsplit(line, WSPCS)))
		return (local_exit(room_data, -1));
	if ((error_status = create_room_if_valid(room_data, &room)) != 0)
		return (local_exit(room_data, error_status));
	if ((error_status = record_room(graph, room)) != 0)
		return (local_exit(room_data, error_status));
	return (local_exit(room_data, 0));
}
