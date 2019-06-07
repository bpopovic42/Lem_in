/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_score.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 20:21:07 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_solution_path(t_path *path)
{
	t_room *room_ptr;

	room_ptr = path->head;
	room_ptr->is_solution = 1; // Should go into t_path
	while (room_ptr && !room_is_end(room_ptr))
	{
		room_ptr->solution_from = room_ptr->from;
		room_ptr->solution_to = room_ptr->to;
		room_ptr = room_ptr->to;
	}
	path->final_length = -1;
}

void	mark_new_route(t_route *route)
{
	t_node *node_ptr;
	t_path *path_ptr;

	node_ptr = route->paths->head;
	while ((path_ptr = get_path_from_node(node_ptr)))
	{
		if (path_ptr->head->recorded)
			mark_solution_path(path_ptr);
		node_ptr = node_ptr->next;
	}
}

void	remove_previous_route_marks(t_graph *graph)
{
	t_room *next_ptr;
	size_t i;

	i = 0;
	while (i < graph->room_list->size)
	{
		next_ptr = ft_vector_get(graph->room_list, i);
		if (!room_is_start(next_ptr))
		{
			next_ptr->is_solution = 0;
			next_ptr->solution_from = NULL;
			next_ptr->solution_to = NULL;
		}
		i++;
	}
}

#include "ft_printf.h"

int		new_score_is_better(t_score *previous, t_score *new)
{
	if (!previous || previous->output_size < 0)
		return (1);
	ft_printf("New score value : %d\n", new->output_size);
	if ((new->output_size >= 0 && new->output_size <= previous->output_size)
			|| previous->output_size < 0)
				return (1);
	return (0);
}

void	remove_recorded_mark(t_path ***path_container)
{
	t_path *path;

	path = **path_container;
	path->head->recorded = 0;
}

int		update_score(t_graph *graph, t_route *route)
{
	t_score *new_score;

	if (!(new_score = score_new()))
		return (-1);
	new_score->total_ants = graph->ants;
	get_new_score(route, &new_score);
	if (new_score_is_better(route->score, new_score))
	{
		ft_putendl("better");
		if (route->score)
			free_score(&route->score);
		route->score = new_score;
		remove_previous_route_marks(graph);
		mark_new_route(route);
	}
	ft_lstiter(route->paths, (void*)&remove_recorded_mark);
	return (0);
}
