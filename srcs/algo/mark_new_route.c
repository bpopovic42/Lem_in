/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_new_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:32:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 19:31:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	mark_solution_path(t_path *path)
{
	t_room *room_ptr;

	path->is_solution = 1;
	room_ptr = path->head;
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
			print_dbg(0, "\tMarking path %s of final length %d\n\t",
				path_ptr->head->name, path_ptr->final_length);
			path_ptr->head->solution_len = path_ptr->final_length;
			mark_solution_path(path_ptr);
		}
		node_ptr = node_ptr->next;
	}
}
