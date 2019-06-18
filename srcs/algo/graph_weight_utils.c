/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_weight_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 18:25:24 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 18:29:22 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	weight_room(t_room *src, t_room *target, t_room *room, int new_dist)
{
	if ((room->end_distance >= 0 && new_dist < room->end_distance)
		|| (room->end_distance < 0 && room != src && room != target))
	{
		if (!room->blocked)
		{
			room->cleaned = 0;
			room->end_distance = new_dist;
			return (1);
		}
	}
	return (0);
}

int			weight_graph(t_queue *bfs, t_room *src, t_room *target)
{
	t_room	*current;
	t_room	*next_ptr;
	t_node	*links_ptr;

	bfs_add(bfs, src);
	src->end_distance = 0;
	while (bfs->size > 0)
	{
		current = bfs_pop(bfs);
		links_ptr = current->links->head;
		while (links_ptr)
		{
			next_ptr = get_room_from_node(links_ptr);
			if (weight_room(src, target, next_ptr, current->end_distance + 1))
				bfs_add(bfs, next_ptr);
			links_ptr = links_ptr->next;
		}
	}
	return (0);
}

void	clean_weight(t_graph *graph)
{
	size_t i;
	t_room *next_ptr;

	i = 0;
	while (i < graph->room_list->size)
	{
		next_ptr = ft_vector_get(graph->room_list, i);
		if (next_ptr != graph->start && next_ptr->end_distance >= 0)
			next_ptr->end_distance = -1;
		i++;
	}
}

void	reweight_graph(t_graph *graph, t_queue *bfs)
{
	clean_weight(graph);
	weight_graph(bfs, graph->end, graph->start);
}
