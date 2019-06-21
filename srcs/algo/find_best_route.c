/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:39:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/19 17:19:35 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	clean_path_lengths(t_path ***path)
{
	(**path)->length = -1;
	(**path)->final_length = -1;
}

static int	set_break_flag(int *break_flag, t_node *node_ptr)
{
	if (!node_ptr && !*break_flag)
	{
		*break_flag = 1;
		return (1);
	}
	return (0);
}

static void	mark_first_path(t_graph *graph, t_path *first_path, t_queue *bfs)
{
	reweight_graph(graph, bfs);
	mark_path(first_path);
}

static void	clean_graph_and_paths(t_graph *graph, t_list *paths)
{
	clean_graph(graph);
	ft_lstiter(paths, (void*)&clean_path_lengths);
}

int			find_best_route(t_graph *graph, t_route *route, t_queue *bfs)
{
	int		break_flag;
	t_path	*first_path;
	t_node	*node_ptr;

	break_flag = 0;
	first_path = NULL;
	node_ptr = route->paths->head;
	while (node_ptr)
	{
		algo_dbg(0, "\t--- NEXT TURN ---\n");
		clean_graph_and_paths(graph, route->paths);
		first_path = get_path_from_node(node_ptr);
		algo_dbg(0, "\t(1st path is %s)\n", first_path->head->name);
		mark_first_path(graph, first_path, bfs);
		mark_next_paths(graph, route->paths, bfs);
		update_score(graph, route);
		if ((!break_flag || !break_link(first_path)))
			node_ptr = node_ptr->next;
		if (set_break_flag(&break_flag, node_ptr))
			node_ptr = route->paths->head;
		algo_dbg(1, "", NULL);
	}
	return (0);
}
