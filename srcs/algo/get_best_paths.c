/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:27:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/13 20:46:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		sort_by_end_distance(void *node_a, void *node_b)
{
	t_room *room_a;
	t_room *room_b;

	room_a = *(t_room**)node_a;
	room_b = *(t_room**)node_b;
	return (room_a->end_distance < room_b->end_distance);
}

void	assign_paths_ids(t_list *start_rooms)
{
	int		i;
	t_node	*room_ptr;

	i = 0;
	room_ptr = start_rooms->head;
	while (room_ptr)
	{
		(*(t_room**)room_ptr->data)->pid = i;
		room_ptr = room_ptr->next;
		i++;
	}
}

t_list	*get_sorted_start_rooms(t_room *start)
{
	t_room	*ptr;
	t_node	*links_ptr;
	t_list	*start_rooms;

	ptr = NULL;
	if (!(start_rooms = ft_lstnew()))
		return (NULL);
	if (start && start->links)
	{
		links_ptr = start->links->head;
		while (links_ptr)
		{
			ptr = *(t_room**)links_ptr->data;
			if (ptr && ptr->end_distance >= 0)
			{
				if (ft_lstadd_data(start_rooms, &ptr, sizeof(ptr)) < 0)
					return (NULL);
			}
			links_ptr = links_ptr->next;
		}
	}
	ft_lstsort(start_rooms, &sort_by_end_distance);
	assign_paths_ids(start_rooms);
	return (start_rooms);
}

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

void	mark_path(t_room *initial_room)
{
	t_room	*ptr;
	t_room	*from;

	from = initial_room;
	from->start_distance = 1;
	ptr = NULL;
	if (room_is_end(initial_room))
	{
		initial_room->blocked = 1;
		initial_room->final_distance = 1;
		return;
	}
	while (!room_is_end(ptr) && (ptr = get_shortest_link(from)))
	{
		from->to = ptr;
		from->blocked = 1;
		if (!room_is_end(ptr))
		{
			ptr->pid = from->pid;
			ptr->start_distance = from->start_distance + 1;
			ptr->from = from;
			from = ptr;
		}
	}
	if (from && room_is_end(ptr))
		initial_room->final_distance = from->start_distance;
}

int		find_paths_simple(t_graph *graph, t_list *srcs, t_queue *bfs, int *sol)
{
	t_node	*room_ptr;
	t_room	*next_path;

	room_ptr = srcs->head;
	next_path = NULL;
	while (room_ptr)
	{
		clean_graph(graph);
		weight_graph(bfs, graph->end, graph->start);
		next_path = (*(t_room**)room_ptr->data);
		while ((next_path = get_shortest_link(graph->start)))
		{
			mark_path(next_path);
			clean_weight(graph);
			weight_graph(bfs, graph->end, graph->start);
		}
		compute_solution(srcs, sol, graph->ants);
		room_ptr = room_ptr->next;
	}
	return (0);
}

int		find_paths_br(t_graph *graph, t_list *srcs, t_queue *bfs, int *sol)
{
	t_node	*room_ptr;
	t_room	*next_path;

	room_ptr = srcs->head;
	next_path = NULL;
	while (room_ptr)
	{
		clean_graph(graph);
		weight_graph(bfs, graph->end, graph->start);
		next_path = (*(t_room**)room_ptr->data);
		while ((next_path = get_shortest_link(graph->start)))
		{
			mark_path(next_path);
			clean_weight(graph);
			weight_graph(bfs, graph->end, graph->start);
		}
		compute_solution(srcs, sol, graph->ants);
		if (!break_link((*(t_room**)room_ptr->data)))
			room_ptr = room_ptr->next;
		clean_weight(graph);
	}
	clean_graph(graph);
	return (0);
}

int		get_best_paths(t_graph *graph)
{
	t_list	*start_rooms;
	t_queue	*bfs;
	int		solution;

	solution = -1;
	if (init_bfs_queue(&bfs, graph->nbr_of_rooms) < 0)
		return (-1);
	weight_graph(bfs, graph->end, graph->start);
	if (!(start_rooms = get_sorted_start_rooms(graph->start)))
		return (-1);
	find_paths_simple(graph, start_rooms, bfs, &solution);
	find_paths_br(graph, start_rooms, bfs, &solution);
	ft_printf("%d ", solution);
	return (0);
}
