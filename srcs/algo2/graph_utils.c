/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:49:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/13 14:44:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	clean_graph(t_graph *graph)
{
	size_t i;
	t_room *next_ptr;

	i = 0;
	while (i < graph->room_list->size)
	{
		next_ptr = ft_vector_get(graph->room_list, i);
		if (!room_is_start(next_ptr) && !next_ptr->cleaned)
		{
			// USE MEMSET
			if (next_ptr->start_distance > 1)
				next_ptr->pid = -1;
			next_ptr->final_distance = -1;
			next_ptr->end_distance = -1;
			next_ptr->solution_len = -1;
			next_ptr->from = NULL;
			next_ptr->to = NULL;
			next_ptr->start_distance = -1; next_ptr->blocked = 0;
			next_ptr->cleaned = 1;
		}
		i++;
	}
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
		{
			next_ptr->end_distance = -1;
		}
		i++;
	}
}

int		weight_graph(t_queue *bfs, t_room *src, t_room *target)
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
			if ((next_ptr != src && next_ptr != target && next_ptr->end_distance < 0)
				|| (next_ptr->end_distance >= 0 && next_ptr->end_distance > current->end_distance + 1))
			{
				if (!next_ptr->blocked)
				{
					next_ptr->cleaned = 0;
					next_ptr->end_distance = current->end_distance + 1;
					bfs_add(bfs, next_ptr);
				}
			}
			links_ptr = links_ptr->next;
		}
	}
	return (0);
}

void	clean_path_length(t_node *path_container)
{
	path_set_length(*(t_path**)path_container->data, -1);
}

void	clean_marks(t_graph *graph, t_list *paths)
{
	clean_graph(graph);
	ft_lstiter(paths, &clean_path_length);
}

void	reweight_graph(t_graph *graph, t_list *paths, t_queue *bfs)
{
	clean_weight(graph);
	weight_graph(bfs, graph->end, graph->start);
	//update_paths_length(paths);
	(void)paths;
}
