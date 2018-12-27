/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_link_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:06:07 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/27 16:09:20 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	room_exists(t_graph *graph, char *room)
{
	size_t i;

	i = 0;
	if (!graph->size || !graph->room_list)
		return (0);
	while (i < graph->size)
	{
		if (!ft_strcmp(graph->room_list->data[i], room))
			return (1);
		i++;
	}
	return (0);
}

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

static int	local_return(char *msg, char **rooms, int return_value)
{
	if (msg)
		lemin_perror(msg);
	if (rooms)
		ft_delarray(rooms);
	return (return_value);
}

int			record_link_if_valid(t_graph *graph, const char *link)
{
	char	**rooms;

	rooms = ft_strsplit(link, "-");
	if (!ft_strcmp(rooms[0], rooms[1]))
		return (local_return("Room links to itself.", rooms, -1));
	else if (!room_exists(graph, rooms[0]) || !room_exists(graph, rooms[1]))
		return (local_return("Linked room doesn't exist.", rooms, -1));
	else if (link_exists(graph, rooms[0], rooms[1]))
		return (local_return("Link already exists.", rooms, -1));
	record_link(graph, rooms[0], rooms[1]);
	return (local_return(NULL, rooms, 0));
}
