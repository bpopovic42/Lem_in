/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_room_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/30 20:13:12 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

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

static int		room_conflict(t_graph *graph, t_room *room)
{
	t_room	*ptr;
	char	*tmp;

	size_t	i;

	i = 0;
	if (!graph->rooms || !graph->rooms->size)
		return (0);
	while (i < graph->room_list->size)
	{
		tmp = ft_vector_get(graph->room_list, i);
		if ((ptr = ft_hashget_data(graph->rooms, tmp)))
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

int				record_room_if_valid(t_graph *graph, char **input)
{
	t_room	*room;
	char	*cmd;

	cmd = get_last_command(graph);
	if (input && is_valid(input))
	{
		room = record_room(graph, input, &cmd);
		if (!room_conflict(graph, room))
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
