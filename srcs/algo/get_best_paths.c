/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:27:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/14 21:21:01 by bopopovi         ###   ########.fr       */
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

void	mark_next_paths(t_graph *graph, t_queue *bfs)
{
	t_room *initial_room_ptr;

	initial_room_ptr = NULL;
	while ((initial_room_ptr = get_shortest_link(graph->start)))
	{
		mark_path(initial_room_ptr);
		clean_weight(graph);
		weight_graph(bfs, graph->end, graph->start);
	}
}

int		find_combinations(t_graph *graph, t_list *srcs, t_queue *bfs, int *sol)
{
	t_node	*room_ptr;
	t_room	*first_path;
	int		break_flag;

	room_ptr = srcs->head;
	first_path = NULL;
	break_flag = 0;
	while (room_ptr)
	{
		first_path = (*(t_room**)room_ptr->data);
		mark_path(first_path);
		mark_next_paths(graph, bfs);
		compute_solution(srcs, sol, graph->ants);
		if (!break_flag && !(room_ptr = room_ptr->next))
		{
			break_flag = 1;
			room_ptr = srcs->head;
		}
		else if (break_flag && !break_link((*(t_room**)room_ptr->data)))
			room_ptr = room_ptr->next;
		clean_graph(graph);
		weight_graph(bfs, graph->end, graph->start);
	}
	clean_graph(graph);
	return (0);
}

void	free_room_ptr(void *data, size_t data_size)
{
	t_room **ptr;

	ptr = (t_room**)data;
	ft_bzero(&ptr, data_size);
	free(ptr);
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
	find_combinations(graph, start_rooms, bfs, &solution);
	ft_printf("%d ", solution);
	free_bfs_queue(&bfs);
	ft_lstdel(start_rooms, &free_room_ptr);
	return (0);
}
