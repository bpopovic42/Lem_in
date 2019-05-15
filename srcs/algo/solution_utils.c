/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:38:49 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/15 20:52:28 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	replace_solution_data(t_solution *old, t_solution *new)
{
	old->value = new->value;
	old->nbr_of_paths = new->nbr_of_paths;
	old->diff = new->diff;
	old->longest_path_size = new->longest_path_size;
}


void	replace_solution_marks(t_list *start_rooms)
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

void	replace_solution(t_list *initial_rooms, t_solution *old, t_solution *new)
{
	replace_solution_data(old, new);
	replace_solution_marks(initial_rooms);
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
