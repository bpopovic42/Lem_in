/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_room_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/20 20:38:35 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room			*record_room(t_graph *graph, char **room_data)
{
	t_pos	coord;
	t_room	*room;

	coord.x = ft_atoi(room_data[1]);
	coord.y = ft_atoi(room_data[2]);
	if (!(room = new_room(room_data[0], &graph->last_command, &coord)))
		return (NULL);
	if (room->command)
	{
		if (!ft_strcmp(room->command, "##start"))
			graph->start = room;
		else if (!ft_strcmp(room->command, "##end"))
			graph->end = room;
	}
	return (room);
}

static int		is_valid(char **input)
{
	char *room;
	char *x;
	char *y;

	room = input[0];
	x = input[1];
	y = input[2];
	if (ft_strchr(room, '-'))
		return (0);
	else if (!ft_is_valid_int(x) || !ft_is_valid_int(y))
		return (0);
	else if (ft_atoi(x) < 0 || ft_atoi(y) < 0)
		return (0);
	else
		return (1);
}

static int		room_conflict(t_graph *graph, t_room *room)
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

int				record_room_if_valid(t_graph *graph, char **input)
{
	t_room	*room;

	if (input && is_valid(input))
	{
		if (!(room = record_room(graph, input)))
			return (-1);
		if (!room_conflict(graph, room))
		{
			graph->nbr_of_rooms++;
			if (ft_vector_append(graph->room_list, room) < 0)
				return (-1);
			if (ft_hashpush_data(graph->rooms, room->name, room, sizeof(*room)) < 0)
				return (-1);
			ft_delarray(input);
			return (0);
		}
		free_room(&room);
	}
	ft_delarray(input);
	return (1);
}
