/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_room_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 20:15:33 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		local_exit(char **room_data, t_room *room, int retval)
{
	if (room_data)
		ft_delarray(room_data);
	if (room)
		free_room(&room);
	return (retval);
}

static int		room_has_conflict(t_graph *graph, t_room *room)
{
	t_room	*ptr;
	size_t	i;

	i = 0;
	if (!graph->rooms || !graph->rooms->size)
		return (0);
	while (i < graph->room_list->size)
	{
		ptr = ft_vector_get(graph->room_list, i);
		if (!ft_strcmp(room->name, ptr->name))
			return (1);
		else if (room->command && ptr->command && !ft_strcmp(room->command, ptr->command))
			return (1);
		else if (room->pos.x == ptr->pos.x && room->pos.y == ptr->pos.y)
			return (1);
		i++;
	}
	return (0);
}

static int		record_room(t_graph *graph, t_room *room)
{
	if (!room_has_conflict(graph, room))
	{
		graph->nbr_of_rooms++;
		if (ft_vector_append(graph->room_list, room) < 0)
			return (-1);
		if (ft_hashpush_data(graph->rooms, room->name, room, sizeof(*room)) < 0)
			return (-1);
		if (graph->last_command)
			room->command = graph->last_command;
		graph->last_command = NULL;
		if (room_is_start(room))
			graph->start = room;
		else if (room_is_end(room))
			graph->end = room;
		return (0);
	}
	return (1);
}

int				record_room_if_valid(t_graph *graph, const char *line)
{
	t_room	*room;
	int		error_status;
	char	**room_data;

	room = NULL;
	error_status = 0;
	if (!(room_data = ft_strsplit(line, WSPCS)))
		return (local_exit(room_data, NULL, -1));
	if ((error_status = create_room_if_valid(room_data, &room)) != 0)
		return (local_exit(room_data, room, error_status));
	if ((error_status = record_room(graph, room)) != 0)
		return (local_exit(room_data, room, error_status));
	return (local_exit(room_data, NULL, 0));
}
