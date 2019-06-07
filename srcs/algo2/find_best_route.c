/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:39:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 19:08:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		find_best_route(t_graph *graph, t_route *route, t_queue *bfs)
{
	t_path	*first_path;
	t_node	*node_ptr;

	first_path = NULL;
	node_ptr = route->paths->head;
	while ((first_path = get_path_from_node(node_ptr)))
	{
		ft_printf("1st path is %s\n", first_path->head->name);
		reweight_graph(graph, route->paths, bfs);
		mark_path(first_path);
		reweight_graph(graph, route->paths, bfs);
		mark_next_paths(graph, route->paths, bfs);
		update_score(graph, route);
		clean_graph(graph);
		node_ptr = node_ptr->next;
	}
	return (0);
}
