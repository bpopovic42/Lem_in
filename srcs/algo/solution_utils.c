/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 20:38:49 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 19:40:49 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	remove_solution_marks_from_path(t_path *path)
{
	t_room *room_ptr;
	t_room *previous_room_ptr;

	room_ptr = path->head->to;
	previous_room_ptr = path->head;
	while (previous_room_ptr && !room_is_end(previous_room_ptr))
	{
		previous_room_ptr->solution_to = NULL;
		previous_room_ptr->solution_from = NULL;
		previous_room_ptr = room_ptr;
		if (room_ptr)
			room_ptr = room_ptr->to;
	}
}

void	mark_solution_path(t_path *path)
{
	t_room *room_ptr;

	room_ptr = path->head;
	room_ptr->is_solution = 1;
	while (room_ptr && !room_is_end(room_ptr))
	{
		room_ptr->solution_from = room_ptr->from;
		room_ptr->solution_to = room_ptr->to;
		room_ptr = room_ptr->to;
	}
	path->length = -1;
}

void	replace_solution_marks(t_list *paths)
{
	t_node	*node_ptr;
	t_path	*path_ptr;

	node_ptr = paths->head;
	//ft_putstr("NEW SOLUTION FOUND :\n");
	while (node_ptr)
	{
		path_ptr = *(t_path**)node_ptr->data;
		if (path_ptr->final_length >= 0)
			mark_solution_path(path_ptr);
		node_ptr = node_ptr->next;
	}
}

void	replace_solution_data(t_solution *old, t_solution *new)
{
	old->value = new->value;
	old->nbr_of_paths = new->nbr_of_paths;
	old->diff = new->diff;
	old->longest_path_size = new->longest_path_size;
}

void	replace_solution(t_list *paths, t_solution *old, t_solution *new)
{
	replace_solution_data(old, new);
	replace_solution_marks(paths);
}

void	clean_previous_solution_marks(t_list *paths)
{
	t_node	*node_ptr;
	t_path	*path_ptr;

	node_ptr = paths->head;
	while (node_ptr)
	{
		path_ptr = *(t_path**)node_ptr->data;
		if (path_ptr->length >= 0)
			path_ptr->length = -1;
		node_ptr = node_ptr->next;
	}
}
