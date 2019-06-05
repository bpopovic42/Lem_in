/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:27:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 14:03:25 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static int	local_exit(t_queue *bfs, t_list *start_rooms, int retval)
{
	if (start_rooms)
		ft_lstdel(start_rooms, &free_room_ptr);
	if (bfs)
		free_bfs_queue(&bfs);
	return (retval);
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

void	path_set_final_length(t_room *initial, int final_length)
{
	initial->final_distance = final_length;
}

void	mark_path(t_room *initial_room)
{
	t_room	*ptr;
	t_room	*from;

	ptr = NULL;
	from = initial_room;
	from->start_distance = 1;
	if (!room_is_end(initial_room))
	{
		while (!room_is_end(ptr) && (ptr = get_shortest_link(from)))
			mark_next_room(&from, &ptr);
		if (path_reached_end(from, ptr))
			path_set_final_length(initial_room, from->start_distance);
	}
	else
	{
		initial_room->blocked = 1;
		initial_room->final_distance = 1;
	}
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

int		find_path_sets(t_graph *graph, t_list *start_rooms,
			t_queue *bfs, t_solution *solution)
{
	t_node	*start_ptr;
	t_room	*first_path;
	int		break_flag;

	start_ptr = start_rooms->head;
	first_path = NULL;
	break_flag = 0;
	while (start_ptr)
	{
		first_path = get_room_from_node(start_ptr);
		mark_path(first_path);
		mark_next_paths(graph, bfs);
		compute_solution(graph, start_rooms, solution, graph->ants);
		if (!break_flag && !(start_ptr = start_ptr->next))
		{
			break_flag = 1;
			start_ptr = start_rooms->head;
		}
		else if (break_flag && !break_link((*(t_room**)start_ptr->data)))
			start_ptr = start_ptr->next;
		clean_graph(graph);
		weight_graph(bfs, graph->end, graph->start);
	}
	clean_graph(graph);
	return (0);
}

int		mark_best_paths(t_graph *graph, t_solution *solution)
{
	t_list	*start_rooms;
	t_queue	*bfs;

	if (init_bfs_queue(&bfs, graph->nbr_of_rooms) < 0)
		return (local_exit(bfs, NULL, -1));
	weight_graph(bfs, graph->end, graph->start);
	if (!(start_rooms = get_sorted_start_rooms(graph->start)))
		return (local_exit(bfs, start_rooms, -1));
	find_path_sets(graph, start_rooms, bfs, solution);
	ft_printf("%d ", solution->value);
	return (local_exit(bfs, start_rooms, 0));
}
