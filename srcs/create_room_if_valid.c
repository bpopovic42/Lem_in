/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/26 16:44:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static t_room	*new_room(char *name, char **com, t_links *links, t_pos *coord)
{
	t_room	*new_room;

	if (!(new_room = malloc(sizeof(*new_room))))
		exit(-1);
	new_room->comment = *com;
	*com = NULL;
	new_room->name = ft_strdup(name);
	new_room->links = links;
	new_room->pos = *coord;
	return (new_room);
}

static t_room	*record_room(t_graph *graph, char **room_data, char **comment)
{
	t_pos	coord;
	t_room	*room;

	coord.x = ft_atoi(room_data[1]);
	coord.y = ft_atoi(room_data[2]);
	room = new_room(room_data[0], comment, NULL, &coord);
	if (room->comment)
	{
		if (!(ft_strcmp(room->comment, "##start")))
		{
			graph->start = room;
		}
		else if (!(ft_strcmp(room->comment, "##end")))
		{
			graph->end = room;
		}
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
	{
		lemin_perror("Room name contains '-'.");
		return (0);
	}
	else if (!ft_is_valid_int(x) || !ft_is_valid_int(y))
	{
		lemin_perror("Invalid integer representation in room's coordinates");
		return (0);
	}
	else if (ft_atoi(x) < 0 || ft_atoi(y) < 0)
	{
		lemin_perror("Negative integer in room coordinates.");
		return (0);
	}
	else
		return (1);
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
		if ((ptr = ft_hashget_data(graph->rooms, graph->room_list->data[i])))
		{
			if (!ft_strcmp(room->name, ptr->name))
			{
				lemin_perror("Duplicated room name.");
				return (1);
			}
			else if (room->pos.x == ptr->pos.x && room->pos.y == ptr->pos.y)
			{
				lemin_perror("Duplicated room coordinates.");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int				create_room_if_valid(char **input, char **cmd, t_graph *graph)
{
	t_room	*room;

	if (input && is_valid(input))
	{
		room = record_room(graph, input, cmd);
		if (!room_has_conflict(graph, room))
		{
			ft_vector_append(graph->room_list, ft_strdup(room->name));
			ft_hashpush_data(graph->rooms, room->name, room, sizeof(*room));
			ft_delarray(input);
			return (0);
		}
		free_room(room);
	}
	ft_delarray(input);
	return (-1);
}
