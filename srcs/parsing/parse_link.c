/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:06:07 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/29 19:40:05 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	local_exit(char **rooms, int return_value)
{
	if (rooms)
		ft_delarray(rooms);
	return (return_value);
}

int			record_link(t_graph *graph, char *room_a, char *room_b)
{
	t_room *ptr_a;
	t_room *ptr_b;

	ptr_a = ft_hashget_data(graph->rooms, room_a);
	ptr_b = ft_hashget_data(graph->rooms, room_b);
	if (!ptr_a->links)
	{
		if (!(ptr_a->links = ft_lstnew()))
			return (-1);
	}
	if (!ptr_b->links)
	{
		if (!(ptr_b->links = ft_lstnew()))
			return (-1);
	}
	if (ft_lstadd_data(ptr_a->links, &ptr_b, sizeof(ptr_b)) < 0)
		return (-1);
	if (ft_lstadd_data(ptr_b->links, &ptr_a, sizeof(ptr_a)) < 0)
		return (-1);
	graph->nbr_of_links++;
	return (0);
}

static int	room_exists(t_graph *graph, char *room)
{
	t_room	*ptr;
	size_t	i;

	i = 0;
	if (!graph->nbr_of_rooms || !graph->room_list)
		return (0);
	while (i < graph->room_list->size)
	{
		ptr = ft_vector_get(graph->room_list, i);
		if (ptr)
		{
			if (!ft_strcmp(ptr->name, room))
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
	t_room	*ptr;
	t_node	*links_ptr;

	ptr = ft_hashget_data(graph->rooms, room_a);
	if (!ptr->links || !ptr->links->size)
		return (0);
	links_ptr = ptr->links->head;
	while (links_ptr)
	{
		if (!ft_strcmp((*(t_room**)links_ptr->data)->name, room_b))
			return (1);
		links_ptr = links_ptr->next;
	}
	return (0);
}

int			parse_link(t_graph *graph, const char *link)
{
	char	**rooms;

	rooms = NULL;
	if (!(rooms = ft_strsplit(link, "-")))
		return (local_exit(rooms, -1));
	if (!ft_strcmp(rooms[0], rooms[1]))
		return (local_exit(rooms, 1));
	else if (!room_exists(graph, rooms[0]) || !room_exists(graph, rooms[1]))
		return (local_exit(rooms, 1));
	else if (link_exists(graph, rooms[0], rooms[1]))
		return (local_exit(rooms, 1));
	if (record_link(graph, rooms[0], rooms[1]) < 0)
		return (local_exit(rooms, -1));
	return (local_exit(rooms, 0));
}
