/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:39:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 16:27:22 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	clean_path_length(t_node *path_container)
{
	path_set_length(*(t_path**)path_container->data, -1);
}

void	clean_marks(t_graph *graph, t_route *route)
{
	clean_graph(graph);
	ft_lstiter(route->paths, &clean_path_length);
}

int		find_best_route(t_graph *graph, t_route *route, t_queue *bfs)
{
	t_path	*first_path;
	t_node	*node_ptr;

	first_path = NULL;
	node_ptr = route->paths->head;
	while ((first_path = get_path_from_node(node_ptr)))
	{
		ft_printf("1st path is %s\n", first_path->head->name);
		clean_marks(graph, route);
		weight_graph(bfs, graph->end, graph->start);
		update_paths_length(route->paths);
		mark_path(first_path);
		mark_next_paths(graph, route->paths, bfs);
		update_score(graph, route);
		clean_graph(graph);
		node_ptr = node_ptr->next;
	}
	clean_graph(graph);
	return (0);
}
