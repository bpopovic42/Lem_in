/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_has_conflict.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:05:46 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 21:16:28 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	room_has_duplicated_name(t_room *a, t_room *b)
{
	return (!ft_strcmp(a->name, b->name));
}

static int	room_has_duplicated_command(t_room *a, t_room *b)
{
	if (a->command && b->command)
		return (!ft_strcmp(a->command, b->command));
	return (0);
}

static int	room_has_duplicated_coordinates(t_room *a, t_room *b)
{
	return (a->pos.x == b->pos.x && a->pos.y == b->pos.y);
}

int			room_has_conflict(t_graph *graph, t_room *room)
{
	t_room	*ptr;
	size_t	i;

	i = 0;
	if (!graph->rooms || !graph->rooms->size)
		return (0);
	while (i < graph->room_list->size)
	{
		ptr = ft_vector_get(graph->room_list, i);
		if (room_has_duplicated_name(room, ptr))
			return (1);
		else if (room_has_duplicated_command(room, ptr))
			return (1);
		else if (room_has_duplicated_coordinates(room, ptr))
			return (1);
		i++;
	}
	return (0);
}
