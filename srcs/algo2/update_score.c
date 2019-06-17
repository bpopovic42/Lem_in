/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_score.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/17 16:53:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	mark_solution_path(t_path *path)
{
	t_room *room_ptr;

	room_ptr = path->head;
	room_ptr->is_solution = 1; // Should go into t_path
	while (room_ptr && !room_is_end(room_ptr))
	{
		print_dbg(0, "%s ", room_ptr->name);
		room_ptr->solution_from = room_ptr->from;
		room_ptr->solution_to = room_ptr->to;
		room_ptr = room_ptr->to;
	}
	print_dbg(1, "", NULL);
	path->final_length = -1;
}

void	mark_new_route(t_route *route)
{
	t_node *node_ptr;
	t_path *path_ptr;

	print_dbg(0, "Marking new route :\n", NULL);
	node_ptr = route->paths->head;
	while ((path_ptr = get_path_from_node(node_ptr)))
	{
		if (path_ptr->final_length >= 0)
		{
			print_dbg(0, "\tMarking path %s of final length %d\n\t", path_ptr->head->name, path_ptr->final_length);
			path_ptr->head->solution_len = path_ptr->final_length;
			mark_solution_path(path_ptr);
		}
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
			next_ptr->solution_len = -1;
			next_ptr->solution_from = NULL;
			next_ptr->solution_to = NULL;
		}
		i++;
	}
}

int		new_score_is_better(t_score *previous, t_score *new)
{
	if (!previous || previous->output_size < 0)
		return (1);
	if ((new->output_size >= 0 && new->output_size < previous->output_size))
				return (1);
	return (0);
}

void	remove_recorded_mark(t_path ***path_container)
{
	t_path *path;

	path = **path_container;
	path->head->recorded = 0;
}

void	replace_score(t_score *old_score, t_score *new_score)
{
	old_score->total_ants = new_score->total_ants;
	old_score->diff = new_score->diff;
	old_score->output_size = new_score->output_size;
	old_score->nbr_of_paths = new_score->nbr_of_paths;
	old_score->longest_path_size = new_score->longest_path_size;
}

int		update_score(t_graph *graph, t_route *route)
{
	t_score new_score;

	init_score(&new_score);
	new_score.total_ants = graph->ants;
	get_new_score(route, &new_score);
	if (new_score_is_better(route->score, &new_score))
	{
		print_dbg(1, "ROUTE IS BETTER", NULL);
		replace_score(route->score, &new_score);
		remove_previous_route_marks(graph);
		mark_new_route(route);
	}
	ft_lstiter(route->paths, (void*)&remove_recorded_mark);
	return (0);
}
