/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:22:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 19:42:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		path_improves_solution(t_path *path, int ants, t_solution *solution)
{
	int new_diff;
	int new_solution;
	int ants_left;

	if (solution->nbr_of_paths == 0)
		return (1);
	new_diff = path->length - solution->longest_path_size;
	new_diff *= solution->nbr_of_paths;
	new_diff += solution->diff;
	ants_left = ants - new_diff;
	if (ants_left > 0 && ants_left / (solution->nbr_of_paths + 1) > 0)
	{
		new_solution = ants_left / (solution->nbr_of_paths + 1);
		new_solution += path->length;
		new_solution += (ants_left % (solution->nbr_of_paths + 1) > 0);
		if (solution->value < 0 || new_solution <= solution->value)
		{
			solution->diff = new_diff;
			return (1);
		}
	}
	return (0);
}

int		new_solution_is_better(t_solution *previous, t_solution *new)
{
	if (previous->value < 0 || (new->value >= 0 && new->value <= previous->value))
		return (1);
	return (0);
}

void	clean_record_flags(t_list *paths)
{
	t_node *node_ptr;
	t_path *path_ptr;

	node_ptr = paths->head;
	while (node_ptr)
	{
		path_ptr = (*(t_path**)node_ptr->data);
		path_ptr->head->recorded = 0;
		node_ptr = node_ptr->next;
	}
}

void	update_solution(t_path *path, int ants, t_solution *solution)
{
	solution->nbr_of_paths += 1;
	path->final_length = path->length;
	solution->value = ((ants - solution->diff) / solution->nbr_of_paths) + path->final_length + ((ants - solution->diff) % solution->nbr_of_paths > 0 ? 1 : 0);
	solution->longest_path_size = path->final_length;
	path->final_length = -1;
}

void	clean_solution_marks_from_graph(t_graph *graph)
{
	size_t i;
	t_room *next_ptr;

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

t_path	*get_next_path(t_list *paths)
{
	t_node *node_ptr;
	t_path *path_ptr;
	t_path *shortest;

	node_ptr = paths->head;
	path_ptr = NULL;
	shortest = NULL;
	while (node_ptr)
	{
		path_ptr = (*(t_path**)node_ptr->data);
		if (path_ptr->length >= 0)
		{
			if (!shortest || path_ptr->length < shortest->length)
			{
				if (path_ptr->head->recorded == 0)
					shortest = path_ptr;
			}
		}
		node_ptr = node_ptr->next;
	}
	if (shortest)
	{
		shortest->head->recorded = 1;
	}
	return (shortest);
}

void	get_current_solution(t_list *paths, int ants, t_solution *solution)
{
	t_path *current;

	current = NULL;
	while ((current = get_next_path(paths)))
	{
		if (path_improves_solution(current, ants, solution))
			update_solution(current, ants, solution);
	}
}

int		compute_solution(t_graph *graph, t_list *paths, t_solution *solution, int ants)
{
	t_solution	new_solution;

	init_solution(&new_solution);
	clean_previous_solution_marks(paths);
	get_current_solution(paths, ants, &new_solution);
	if (new_solution_is_better(solution, &new_solution))
	{
		//ft_printf("BETTER\n");
		clean_solution_marks_from_graph(graph);
		replace_solution(paths, solution, &new_solution);
	}
	clean_record_flags(paths);
	return (0);
}
