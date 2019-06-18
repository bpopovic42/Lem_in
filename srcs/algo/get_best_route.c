/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 19:33:14 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/13 20:27:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
static int	local_exit(t_queue **bfs, int retval)
{
	if (*bfs)
		free_bfs_queue(bfs);
	return (retval);
}

static void	graph_mark_end_distance(t_room *end, t_queue *bfs) //DIRTY
{
	t_room	*current;
	t_room	*next_ptr;
	t_node	*links_ptr;

	bfs_add(bfs, end);
	end->end_distance = 0;
	while (bfs->size > 0)
	{
		current = bfs_pop(bfs);
		links_ptr = current->links->head;
		while (links_ptr)
		{
			next_ptr = *(t_room**)links_ptr->data;
			if (!room_is_end(next_ptr) && !room_is_start(next_ptr) && next_ptr->end_distance < 0)
			{
				next_ptr->end_distance = current->end_distance + 1;
				bfs_add(bfs, next_ptr);
			}
			links_ptr = links_ptr->next;
		}
	}
}

int			initialize_path_heads(t_graph *graph, t_list *paths)
{
	t_room *room;
	t_node *node;
	t_path *tmp;

	room = NULL;
	node = graph->start->links->head;
	tmp = NULL;
	while (node)
	{
		room = get_room_from_node(node);
		if (room->end_distance >= 0)
		{
			if (!(tmp = path_new()))
				return (-1);
			path_set_head(tmp, room);
			if (ft_lstadd_data(paths, &tmp, sizeof(tmp)) < 0)
			{
				free_path(&tmp);
				return (-1);
			}
		}
		node = node->next;
	}
	return (0);
}

int			get_best_route(t_graph *graph, t_route *route)
{
	t_queue	*bfs;

	bfs = NULL;
	if (init_bfs_queue(&bfs, graph->nbr_of_rooms) < 0)
		return (local_exit(&bfs, -1));
	graph_mark_end_distance(graph->end, bfs);
	if (initialize_path_heads(graph, route->paths) < 0)
		return (local_exit(&bfs, -1));
	sort_paths_by_head_distance(route->paths);
	find_best_route(graph, route, bfs);
	return (local_exit(&bfs, 0)); //nbr of paths found
}
