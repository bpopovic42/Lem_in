/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:41:26 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/26 18:44:16 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*new_room(char *name, char **cmd, t_links *links, t_pos *coord)
{
	t_room	*new_room;

	if (!(new_room = malloc(sizeof(*new_room))))
		exit(-1);
	new_room->command = *cmd;
	*cmd = NULL;
	new_room->name = ft_strdup(name);
	new_room->links = links;
	new_room->pos = *coord;
	return (new_room);
}

t_room			*record_room(t_graph *graph, char **room_data, char **cmd)
{
	t_pos	coord;
	t_room	*room;

	coord.x = ft_atoi(room_data[1]);
	coord.y = ft_atoi(room_data[2]);
	room = new_room(room_data[0], cmd, NULL, &coord);
	if (room->command)
	{
		if (!ft_strcmp(room->command, "##start"))
			graph->start = room;
		else if (!ft_strcmp(room->command, "##end"))
			graph->end = room;
	}
	return (room);
}
