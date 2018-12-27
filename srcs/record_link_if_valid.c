/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_link_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:06:07 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/27 14:08:54 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	room_exists(t_graph *graph, char *room)
{
	size_t i;

	i = 0;
	if (graph->size && graph->room_list)
	{
		while (i < graph->size)
		{
			if (!ft_strcmp(graph->room_list->data[i], room))
				return (1);
			i++;
		}
	}
	lemin_perror("Linked room doesn't exist.");
	return (0);
}

static int	link_exists(t_graph *graph, char *room_a, char *room_b)
{
	size_t	i;
	t_room	*ptr;

	i = 0;
	if (!(ptr = ft_hashget_data(graph->rooms, room_a)))
		return (-1);
	if (ptr->links && ptr->links->size)
	{
		while (i < ptr->links->size)
		{
			if (!ft_strcmp(ptr->links->data[i], room_b))
			{
				lemin_perror("Link already exists.");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int		record_link_if_valid(t_graph *graph, const char *link)
{
	char **rooms;

	rooms = NULL;
	if (link && (rooms = ft_strsplit(link, "-")) == NULL)
		exit(-1);
	if (!ft_strcmp(rooms[0], rooms[1]))
	{
		lemin_perror("Room links to itself.");
		return (-1);
	}
	if (room_exists(graph, rooms[0]) && room_exists(graph, rooms[1]))
	{
		if (link_exists(graph, rooms[0], rooms[1]))
		{
			ft_delarray(rooms);
			return (-1);
		}
		else
		{
			record_link(graph, rooms[0], rooms[1]);
			ft_delarray(rooms);
			return (0);
		}
	}
	return (-1);
}
