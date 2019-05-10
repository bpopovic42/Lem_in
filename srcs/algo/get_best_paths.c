/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:27:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/09 21:08:58 by bopopovi         ###   ########.fr       */
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

__attribute__((unused))void	print_end_distance(t_node *node)
{
	t_room *room;

	room = *(t_room**)node->data;
	ft_putnbr(room->end_distance);
	ft_putchar('\n');
}

/*****************************************************************************/

void	print_final(t_node *room_ptr)
{
	t_room *room;

	room = *(t_room**)room_ptr->data;
	if (room->final_distance >= 0)
	{
		ft_printf("path %s fd %d\n", room->name, room->final_distance);
	}
}

void	print_complete_path(t_room *src)
{
	while (src && !room_is_end(src))
	{
		ft_printf("%s\n", src->name);
		src = src->to;
	}
}

__attribute__((unused))void	print_complete(t_list *start_rooms)
{
	t_node *ptr;
	t_room *room;

	ptr = start_rooms->head;
	while (ptr)
	{
		room = *(t_room**)ptr->data;
		if (room->final_distance >= 0)
		{
			ft_printf("PID %d ; LENGTH %d\n", room->pid, room->final_distance);
			print_complete_path(room);
			ft_putendl("\n");
		}
		ptr = ptr->next;
	}
}

/******************************************************************************/

t_room	*get_shortest_link(t_room *src)
{
	t_room	*shortest;
	t_node	*links_ptr;
	t_room	*ptr;

	shortest = NULL;
	ptr = NULL;
	links_ptr = src->links->head;
	//ft_printf("\tLinks for room %s\n", src->name);
	while (links_ptr)
	{
		ptr = *(t_room**)links_ptr->data;
		//ft_printf("\t%s block %d ed %d\n", ptr->name, ptr->blocked, ptr->end_distance);
		if ((ptr != src->from && !room_is_start(ptr) && !ptr->blocked && ptr->end_distance >= 0) || room_is_end(ptr))
		{
			if (room_is_end(ptr))
				return (ptr);
			else
			{
				if (shortest == NULL)
					shortest = ptr;
				else if (shortest->end_distance > ptr->end_distance)
					shortest = ptr;
			}
		}
		links_ptr = links_ptr->next;
	}
	return (shortest);
}

void	mark_path(t_room *initial_room)
{
	t_room	*ptr;
	t_room	*from;

	from = NULL;
	ptr = initial_room;
	ptr->start_distance = 1;
	//ft_printf("PATH %s\n", ptr->name);
	while (ptr)
	{
		//ft_printf("Marking room %s\n", ptr->name);
		if (from)
		{
			from->to = ptr;
			ptr->pid = from->pid;
			ptr->start_distance = from->start_distance + 1;
		}
		ptr->from = from;
		ptr->blocked = 1;
		from = ptr;
		if (room_is_end(ptr))
			break;
		ptr = get_shortest_link(from);
	}
	initial_room->final_distance = from->start_distance - 1;
	//ft_printf("PATH END\n\n");
}

t_room	*get_shortest_path(t_room *start)
{
	int		shortest_distance;
	t_room	*shortest;
	t_node	*links_ptr;
	t_room	*ptr;

	shortest_distance = -1;
	shortest = NULL;
	links_ptr = start->links->head;
	while (links_ptr)
	{
		ptr = *(t_room**)links_ptr->data;
		//ft_printf("get shortest path : room %s, ed : %d\n", ptr->name, ptr->end_distance);
		if (ptr->end_distance >= 0 && !ptr->blocked)
		{
			if (shortest_distance < 0 || (shortest_distance >= 0 && ptr->end_distance < shortest_distance))
			{
				shortest = ptr;
				shortest_distance = shortest->end_distance;
			}
		}
		links_ptr = links_ptr->next;
	}
	//ft_putchar('\n');
	return (shortest);
}

int			clean_graph(t_queue *bfs, t_room *start)
{
	t_room	*current;
	t_room	*next_ptr;
	t_node	*links_ptr;

	bfs_add(bfs, start);
	start->end_distance = -1;
	//ft_printf("CLEAN_START\n");
	while (bfs->size > 0)
	{
		current = bfs_pop(bfs);
		links_ptr = current->links->head;
		while (links_ptr)
		{
			next_ptr = *(t_room**)links_ptr->data;
			//ft_printf("clean %s ? (block %d ed %d clean %d)\n", next_ptr->name, next_ptr->blocked, next_ptr->end_distance, next_ptr->cleaned);
			if (!room_is_start(next_ptr) && !room_is_end(next_ptr) && !next_ptr->cleaned)
			{
				//ft_printf("cleaning %s\n", next_ptr->name);
				if (next_ptr->start_distance > 1)
					next_ptr->pid = -1;
				next_ptr->final_distance = -1;
				next_ptr->end_distance = -1;
				next_ptr->solution_len = -1;
				next_ptr->from = NULL;
				next_ptr->to = NULL;
				next_ptr->start_distance = -1;
				next_ptr->blocked = 0;
				next_ptr->cleaned = 1;
				bfs_add(bfs, next_ptr);
			}
			links_ptr = links_ptr->next;
		}
	}
	//ft_printf("CLEAN_END\n\n");
	return (0);
}

void	tmp_clean_weight(t_graph *graph)
{
	size_t i;
	t_room *next_ptr;

	i = 0;
	while (i < graph->room_list->size)
	{
		next_ptr = ft_vector_get(graph->room_list, i);
		if (next_ptr != graph->start && next_ptr != graph->end && next_ptr->end_distance >= 0)
		{
			next_ptr->end_distance = -1;
		}
		i++;
	}
}

void	tmp_clean_graph(t_graph *graph)
{
	size_t i;
	t_room *next_ptr;

	i = 0;
	while (i < graph->room_list->size)
	{
		next_ptr = ft_vector_get(graph->room_list, i);
		if (!room_is_start(next_ptr) && !room_is_end(next_ptr) && !next_ptr->cleaned)
		{
			if (next_ptr->start_distance > 1)
				next_ptr->pid = -1;
			next_ptr->final_distance = -1;
			next_ptr->end_distance = -1;
			next_ptr->solution_len = -1;
			next_ptr->from = NULL;
			next_ptr->to = NULL;
			next_ptr->start_distance = -1;
			next_ptr->blocked = 0;
			next_ptr->cleaned = 1;
		}
		i++;
	}
}

int		get_best_paths(t_graph *graph)
{
	t_list	*start_rooms;
	t_node	*room_ptr;
	t_room	*next_path;
	t_queue	*bfs;
	int		solution;

	if (init_bfs_queue(&bfs, graph->nbr_of_rooms) < 0)
		return (-1);
	weight_graph(bfs, graph->end, graph->start);
	if (!(start_rooms = get_sorted_start_rooms(graph->start)))
		return (-1);
	room_ptr = start_rooms->head;
	solution = -1;
	while (room_ptr)
	{
		//ft_putendl((*(t_room**)room_ptr->data)->name);
		tmp_clean_graph(graph);
		//clean_graph(bfs, graph->start);
		weight_graph(bfs, graph->end, graph->start);
		next_path = (*(t_room**)room_ptr->data);
		while (next_path)
		{
			next_path->start_distance = 1;
			mark_path(next_path);
			tmp_clean_weight(graph);
			//clean_weight(bfs, graph->end, graph->start);
			weight_graph(bfs, graph->end, graph->start);
			next_path = get_shortest_path(graph->start);
		}
		compute_solution(start_rooms, &solution, graph->ants);
		//ft_lstiter(start_rooms, &print_final);
		//ft_putchar('\n');
		room_ptr = room_ptr->next;
	}
	room_ptr = start_rooms->head;
	tmp_clean_weight(graph);
	while (room_ptr)
	{
		//ft_putendl((*(t_room**)room_ptr->data)->name);
		tmp_clean_graph(graph);
		//clean_graph(bfs, graph->start);
		weight_graph(bfs, graph->end, graph->start);
		next_path = (*(t_room**)room_ptr->data);
		while (next_path)
		{
			if (next_path->end_distance >= 0)
			{
				next_path->start_distance = 1;
				mark_path(next_path);
				tmp_clean_weight(graph);
				//clean_weight(bfs, graph->end, graph->start);
				weight_graph(bfs, graph->end, graph->start);
			}
			next_path = get_shortest_path(graph->start);
		}
		compute_solution(start_rooms, &solution, graph->ants);
		//ft_lstiter(start_rooms, &print_final);
		//ft_putchar('\n');
		if (!break_link((*(t_room**)room_ptr->data)))
			room_ptr = room_ptr->next;
		tmp_clean_weight(graph);
	}
	tmp_clean_graph(graph);
	//clean_graph(bfs, graph->start);
	//print_complete(start_rooms);
	ft_printf("%d ", solution);
	return (0);
}
