/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:22:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/16 18:25:15 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

t_room	*get_next_path(t_list *paths)
{
	t_node *node_ptr;
	t_room *room_ptr;
	t_room *shortest;

	node_ptr = paths->head;
	room_ptr = NULL;
	shortest = NULL;
	while (node_ptr)
	{
		room_ptr = (*(t_room**)node_ptr->data);
		if (room_ptr->final_distance >= 0)
		{
			if (!shortest || room_ptr->final_distance < shortest->final_distance)
			{
				if (room_ptr->recorded == 0)
					shortest = room_ptr;
			}
		}
		node_ptr = node_ptr->next;
	}
	if (shortest)
		shortest->recorded = 1;
	return (shortest);
}

int		path_improves_solution(t_room *path_head, int ants, t_solution *solution)
{
	int new_diff;
	int new_solution;
	int ants_left;

	if (solution->nbr_of_paths == 0)
		return (1);
	new_diff = path_head->final_distance - solution->longest_path_size;
	new_diff *= solution->nbr_of_paths;
	new_diff += solution->diff;
	ants_left = ants - new_diff;
	if (ants_left > 0 && ants_left / (solution->nbr_of_paths + 1) > 0)
	{
		new_solution = ants_left / (solution->nbr_of_paths + 1);
		new_solution += path_head->final_distance ;
		new_solution += (ants_left % (solution->nbr_of_paths + 1) > 0);
		if (solution->value < 0 || new_solution <= solution->value)
		{
			solution->diff = new_diff;
			return (1);
		}
	}
	return (0);
}

void	update_solution(t_room *path_head, int ants, t_solution *solution)
{
	solution->nbr_of_paths += 1;
	path_head->solution_len = path_head->final_distance;
	solution->value = ((ants - solution->diff) / solution->nbr_of_paths) + path_head->final_distance + ((ants - solution->diff) % solution->nbr_of_paths > 0 ? 1 : 0);
	solution->longest_path_size = path_head->final_distance;
}

void	get_current_solution(t_list *start_rooms, int ants, t_solution *solution)
{
	t_room	*current;

	current = NULL;
	while ((current = get_next_path(start_rooms)))
	{
		if (path_improves_solution(current, ants, solution))
			update_solution(current, ants, solution);
	}
}

int		new_solution_is_better(t_solution *previous, t_solution *new)
{
	if (previous->value < 0 || (new->value >= 0 && new->value <= previous->value))
		return (1);
	return (0);
}

void	clean_record_flags(t_list *start_rooms)
{
	t_node *node_ptr;
	t_room *room_ptr;

	node_ptr = start_rooms->head;
	while (node_ptr)
	{
		room_ptr = (*(t_room**)node_ptr->data);
		room_ptr->recorded = 0;
		node_ptr = node_ptr->next;
	}
}

int		compute_solution(t_list *start_rooms, t_solution *solution, int ants)
{
	t_solution	new_solution;

	init_solution(&new_solution);
	clean_previous_solution_marks(start_rooms);
	get_current_solution(start_rooms, ants, &new_solution);
	if (new_solution_is_better(solution, &new_solution))
		replace_solution(start_rooms, solution, &new_solution);
	clean_record_flags(start_rooms);
	return (0);
}
