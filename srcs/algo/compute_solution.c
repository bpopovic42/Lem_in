/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:22:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/15 21:02:06 by bopopovi         ###   ########.fr       */
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

void	get_current_solution(t_list *start_rooms, int ants, t_solution *solution)
{
	t_room	*current;
	int		current_solution;

	current = NULL;
	current_solution = -1;
	while ((current = get_next_path(start_rooms)))
	{
		if (solution->nbr_of_paths > 0 && (ants - (solution->diff + ((current->final_distance - solution->longest_path_size) * solution->nbr_of_paths))) / solution->nbr_of_paths <= 0)
			break;
		if (solution->nbr_of_paths > 0)
			solution->diff += (current->final_distance - solution->longest_path_size) * solution->nbr_of_paths;
		solution->nbr_of_paths += 1;
		current->solution_len = current->final_distance;
		current_solution = ((ants - solution->diff) / solution->nbr_of_paths) + current->final_distance + ((ants - solution->diff) % solution->nbr_of_paths > 0 ? 1 : 0);
		if (solution->value < 0 || (current_solution >= 0 && current_solution < solution->value))
		{
			solution->value = current_solution;
			solution->longest_path_size = current->final_distance;
		}
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

	node_ptr = start_rooms->head;
	while (node_ptr)
	{
		(*(t_room**)node_ptr->data)->recorded = 0;
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
