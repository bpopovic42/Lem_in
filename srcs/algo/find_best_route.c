/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:39:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 17:56:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void	tmp_clean_paths(t_list *paths)
{
	t_node *node_ptr;
	t_path *path;

	node_ptr = paths->head;
	while ((path = get_path_from_node(node_ptr)))
	{
		path->length = -1;
		path->final_length = -1;
		node_ptr = node_ptr->next;
	}
}

int			find_best_route(t_graph *graph, t_route *route, t_queue *bfs)
{
	t_path	*first_path;
	t_node	*node_ptr;
	bool	break_flag;

	int tmp_turn = 0;

	first_path = NULL;
	node_ptr = route->paths->head;
	break_flag = false;
	tmp_clean_paths(route->paths); // ISSUE WAS HERE :')
	while ((first_path = get_path_from_node(node_ptr)))
	{
		print_dbg(0, "\t--- TURN %d ---\n", tmp_turn);
		print_dbg(0, "\t(1st path is %s)\n", first_path->head->name);
		reweight_graph(graph, bfs);
		mark_path(first_path);
		mark_next_paths(graph, route->paths, bfs);
		update_score(graph, route);
		if (!break_flag || break_link(first_path) == 0)
			node_ptr = node_ptr->next;
		if (!node_ptr && !break_flag)
		{
			break_flag = true;
			node_ptr = route->paths->head;
		}
		clean_graph(graph);
		tmp_clean_paths(route->paths);
		print_dbg(1, "", NULL);
		tmp_turn++;
	}
	return (0);
}
