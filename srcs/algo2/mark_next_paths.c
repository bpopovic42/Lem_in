/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_next_paths.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:59:29 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 19:11:20 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		path_is_shorter(t_path *path, t_path *shortest)
{

	if (path->head->blocked)
		return (0);
	else if (path->length >= 0)
	{
		if (shortest == NULL || shortest->length > path->length)
			return (1);
	}
	return (0);
}

t_path	*get_next_shortest_path(t_list *paths)
{
	t_node *node_ptr;
	t_path *path_ptr;
	t_path *shortest;

	node_ptr = paths->head;
	path_ptr = NULL;
	shortest = NULL;
	while (node_ptr)
	{
		path_ptr = get_path_from_node(node_ptr);
		if (path_is_shorter(path_ptr, shortest))
			shortest = path_ptr;
		node_ptr = node_ptr->next;
	}
	return (shortest);
}

void	mark_next_paths(t_graph *graph, t_list *paths, t_queue *bfs)
{
	t_path *path_ptr;

	path_ptr = NULL;
	reweight_graph(graph, paths, bfs);
	while ((path_ptr = get_next_shortest_path(paths)))
	{
		mark_path(path_ptr);
		reweight_graph(graph, paths, bfs);
	}
}
