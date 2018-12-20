/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/20 19:37:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static t_room	*new_room(char *name, char *com, t_links *links, t_pos *coord)
{
	t_room	*new_room;

	if (!(new_room = malloc(sizeof(*new_room))))
		exit(-1);
	if (com)
	{
		new_room->comment = ft_strdup(com);
		com = NULL;
	}
	new_room->name = ft_strdup(name);
	new_room->links = links;
	new_room->pos = *coord;
	return (new_room);
}

static void		record_room(t_graph *graph, char **room_data, char *comment)
{
	t_pos	coord;
	t_room	*room;
	t_hash	*new_hash;

	coord.x = ft_atoi(room_data[1]);
	coord.y = ft_atoi(room_data[2]);
	room = new_room(room_data[0], comment, NULL, &coord);
	new_hash = ft_hashnew(room->name, room, sizeof(*room));
	ft_hashpush(graph->rooms, new_hash);
	if (comment)
	{
		if (!(ft_strcmp(comment, "##start")))
			graph->start = room;
		else if (!(ft_strcmp(comment, "##end")))
			graph->end = room;
	}
}

int		check_position_conflict(t_graph *graph, int x, int y)
{
	int i;
	t_hash *room_ptr;

	i = 0;
	room_ptr = NULL;
	if (graph->rooms && graph->rooms->size != 0)
	{
		while (i < (int)graph->room_list->size)
		{
			room_ptr = ft_hashget(graph->rooms, graph->room_list->data[i]);
			if (room_ptr)
			{
				t_room *test = room_ptr->data;
				if (test->pos.x == (size_t)x && test->pos.y == (size_t)y)
					return (1);
			}
			i++;
		}
	}
	return (0);
}

int		get_room(char *input, char *comment, t_graph *graph)
{
	char **tmp;

	if (input)
	{
		tmp = ft_strsplit(input, WSPCS);
		ft_vector_append(graph->room_list, (void*)ft_strdup(tmp[0]));
		if (check_position_conflict(graph, ft_atoi(tmp[1]), ft_atoi(tmp[2])))
			return (-1);
		record_room(graph, tmp, comment);
		ft_delarray(tmp);
		return (0);
	}
	return (-1);
}
