/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:22:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/15 18:55:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

t_room	*get_next_path(t_list *paths)
{
	t_node *ptr;
	t_room *shortest;

	ptr = paths->head;
	shortest = NULL;
	while (ptr)
	{
		if ((*(t_room**)ptr->data)->final_distance >= 0)
		{
			if (!shortest || (*(t_room**)ptr->data)->final_distance < shortest->final_distance)
			{
				if ((*(t_room**)ptr->data)->recorded == 0)
					shortest = (*(t_room**)ptr->data);
			}
		}
		ptr = ptr->next;
	}
	if (shortest)
		shortest->recorded = 1;
	return (shortest);
}

void	remove_solution_marks_from_path(t_room *src)
{
	t_room *room_ptr;
	t_room *previous_room_ptr;

	room_ptr = src->to;
	previous_room_ptr = src;
	while (previous_room_ptr && !room_is_end(previous_room_ptr))
	{
		previous_room_ptr->solution_to = NULL;
		previous_room_ptr->solution_from = NULL;
		previous_room_ptr = room_ptr;
		if (room_ptr)
			room_ptr = room_ptr->to;
	}
}

void	mark_solution_path(t_room *src)
{
	t_room *room_ptr;

	room_ptr = src;
	while (room_ptr && !room_is_end(room_ptr))
	{
		room_ptr->solution_from = room_ptr->from;
		room_ptr->solution_to = room_ptr->to;
		room_ptr = room_ptr->to;
	}
}

void	replace_previous_solution(t_list *start_rooms)
{
	t_node	*ptr;
	t_room	*room_ptr;

	ptr = start_rooms->head;
	while (ptr)
	{
		room_ptr = *(t_room**)ptr->data;
		if (room_ptr->solution_to != NULL)
			remove_solution_marks_from_path(room_ptr);
		if (room_ptr->solution_len >= 0)
		{
			mark_solution_path(room_ptr);
		}
		ptr = ptr->next;
	}
}

void	clean_previous_solution_marks(t_list *start_rooms)
{
	t_node	*node_ptr;
	t_room	*room_ptr;

	node_ptr = start_rooms->head;
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->solution_len >= 0)
			room_ptr->solution_len = -1;
		node_ptr = node_ptr->next;
	}
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

int		compute_solution(t_list *start_rooms, t_solution *solution, int ants)
{
	t_solution	new_solution;

	clean_previous_solution_marks(start_rooms);
	init_solution(&new_solution);
	get_current_solution(start_rooms, ants, &new_solution);
	if (new_solution_is_better(solution, &new_solution))
	{
		solution->value = new_solution.value;
		solution->nbr_of_paths = new_solution.nbr_of_paths;
		solution->diff = new_solution.diff;
		solution->longest_path_size = new_solution.longest_path_size;
		replace_previous_solution(start_rooms);
		t_node *ptr = start_rooms->head;
		t_room *lolptr;
		//ft_printf("Computed diff %d\n", diff);
		while (ptr)
		{
			lolptr = (*(t_room**)ptr->data);
			if (lolptr->solution_len >= 0)
			{
				//ft_printf("path %s of len %d\n", lolptr->name, lolptr->solution_len);
			}
			ptr = ptr->next;
		}
		//ft_putchar('\n');
	}
	t_node *node_ptr;
	node_ptr = start_rooms->head;
	while (node_ptr)
	{
		(*(t_room**)node_ptr->data)->recorded = 0;
		node_ptr = node_ptr->next;
	}
	return (0);
}
