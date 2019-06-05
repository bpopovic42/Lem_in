/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:27:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 19:41:27 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		link_is_shorter(t_room *src, t_room *link, t_room *shortest)
{
	if (link == src->from || room_is_start(link) || link->blocked)
		return (0);
	else if (link->end_distance >= 0)
	{
		if (shortest == NULL || shortest->end_distance > link->end_distance)
			return (1);
	}
	return (0);
}

t_room	*get_shortest_link(t_room *src)
{
	t_node	*link_ptr;
	t_room	*shortest;
	t_room	*link;

	link_ptr = src->links->head;
	shortest = NULL;
	link = NULL;
	while (link_ptr)
	{
		link = *(t_room**)link_ptr->data;
		if (room_is_end(link))
		{
			if (room_is_start(src) && link->blocked)
				return (NULL);
			return (link);
		}
		else if (link_is_shorter(src, link, shortest))
			shortest = link;
		link_ptr = link_ptr->next;
	}
	return (shortest);
}

int		path_is_shorter(t_path *path, t_path *shortest)
{

	if (path->head->blocked)
		return (0);
	else if (path->head->end_distance >= 0)
	{
		if (shortest == NULL || shortest->head->end_distance > path->head->end_distance)
			return (1);
	}
	return (0);
}

t_path	*get_next_shortest_path(t_list *paths)
{
	t_node *node_ptr;
	t_path *path_ptr;
	t_path *shortest;

	node_ptr = paths->head;
	path_ptr = NULL;
	shortest = NULL;
	while (node_ptr)
	{
		path_ptr = *(t_path**)node_ptr->data;
		if (path_is_shorter(path_ptr, shortest))
			shortest = path_ptr;
		node_ptr = node_ptr->next;
	}
	return (shortest);
}

void	mark_next_room(t_room **from, t_room **next)
{
	(*from)->to = (*next);
	(*from)->blocked = 1;
	if (!room_is_end((*next)))
	{
		(*next)->pid = (*from)->pid;
		(*next)->start_distance = (*from)->start_distance + 1;
		(*next)->from = (*from);
		(*from) = (*next);
	}
}

int		path_reached_end(t_room *from, t_room *last)
{
	return (from && room_is_end(last));
}

void	path_set_final_length(t_path *path, int length)
{
	path->length = length;
}

void	mark_path(t_path *path)
{
	t_room	*ptr;
	t_room	*from;

	ptr = NULL;
	from = path->head;
	from->start_distance = 1;
	if (!room_is_end(from))
	{
		while (!room_is_end(ptr) && (ptr = get_shortest_link(from)))
			mark_next_room(&from, &ptr);
		if (path_reached_end(from, ptr))
			path_set_final_length(path, from->start_distance);
	}
	else
	{
		path->head->blocked = 1;
		path->length = 1;
	}
}

void	mark_next_paths(t_graph *graph, t_queue *bfs, t_list *paths)
{
	t_path *path_ptr;

	path_ptr = NULL;
	while ((path_ptr = get_next_shortest_path(paths)))
	{
		mark_path(path_ptr);
		clean_weight(graph);
		weight_graph(bfs, graph->end, graph->start);
	}
}

int		find_path_sets(t_graph *graph, t_list *paths,
			t_queue *bfs, t_solution *solution)
{
	t_node	*node_ptr;
	t_path	*first_path;
	int		break_flag;

	node_ptr = paths->head;
	first_path = NULL;
	break_flag = 0;
	while (node_ptr)
	{
		first_path = *(t_path**)node_ptr->data;
		mark_path(first_path);
		mark_next_paths(graph, bfs, paths);
		compute_solution(graph, paths, solution, graph->ants);
		if (!break_flag && !(node_ptr = node_ptr->next))
		{
			break_flag = 1;
			node_ptr = paths->head;
		}
		else if (break_flag && !break_link((*(t_path**)node_ptr->data)))
			node_ptr = node_ptr->next;
		clean_graph(graph);
		weight_graph(bfs, graph->end, graph->start);
	}
	clean_graph(graph);
	return (0);
}

int		mark_best_paths(t_graph *graph, t_queue *bfs, t_list *paths, t_solution *solution)
{
	clean_graph(graph);
	weight_graph(bfs, graph->end, graph->start);
	sort_paths(paths);
	find_path_sets(graph, paths, bfs, solution);
	ft_printf("%d ", solution->value);
	return (0);
}
