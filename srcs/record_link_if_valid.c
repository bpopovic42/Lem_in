/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_link_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:06:07 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/26 15:28:35 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	local_exit(char **rooms, int return_value)
{
	if (rooms)
		ft_delarray(rooms);
	return (return_value);
}

static int	room_exists(t_graph *graph, char *room)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!graph->nbr_of_rooms || !graph->room_list)
		return (0);
	while (i < graph->room_list->size)
	{
		ptr = ft_vector_get(graph->room_list, i);
		if (ptr)
		{
			if (!ft_strcmp(ptr, room))
				return (1);
		}
		i++;
	}
	return (0);
}

/*
** Following function might be improved by passing read file
** And running strcmp against it
*/

static int	link_exists(t_graph *graph, char *room_a, char *room_b)
{
	size_t	i;
	t_room	*ptr;

	i = 0;
	ptr = ft_hashget_data(graph->rooms, room_a);
	if (!ptr->links || !ptr->links->size)
		return (0);
	while (i < ptr->links->size)
	{
		if (!ft_strcmp(ptr->links->data[i], room_b))
			return (1);
		i++;
	}
	return (0);
}

int			record_link_if_valid(t_graph *graph, const char *link)
{
	char	**rooms;

	rooms = ft_strsplit(link, "-");
	if (!ft_strcmp(rooms[0], rooms[1]))
		return (local_exit(rooms, -1));
	else if (!room_exists(graph, rooms[0]) || !room_exists(graph, rooms[1]))
		return (local_exit(rooms, -1));
	else if (link_exists(graph, rooms[0], rooms[1]))
		return (local_exit(rooms, -1));
	record_link(graph, rooms[0], rooms[1]);
	return (local_exit(rooms, 0));
}
