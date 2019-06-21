/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:06:36 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/21 13:19:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_remaining_ants_to_paths(t_route *route, int ants)
{
	int		div_ants;
	int		surplus;
	t_node	*node_ptr;
	t_path	*path_ptr;

	div_ants = (ants - route->score->diff) / route->paths->size;
	surplus = (ants - route->score->diff) % route->paths->size;
	node_ptr = route->paths->head;
	while (node_ptr)
	{
		path_ptr = get_path_from_node(node_ptr);
		path_ptr->ants += div_ants;
		if (surplus)
		{
			path_ptr->ants += 1;
			surplus--;
		}
		node_ptr = node_ptr->next;
	}
}

static int	set_paths_ants(t_route *route, int ants)
{
	t_path	*path;
	t_node	*node;

	path = NULL;
	node = route->paths->head;
	while (node)
	{
		path = get_path_from_node(node);
		path->ants = route->score->longest_path_size - path->head->solution_len;
		algo_dbg(0, "For path %s of length %d, %d surplus ants\n",
			path->head->name, path->head->solution_len, path->ants);
		node = node->next;
	}
	add_remaining_ants_to_paths(route, ants);
	return (0);
}

static void	print_ants_route(t_route *route, int ants, t_room *end)
{
	int		ants_count;
	int		first_ant;
	t_node	*node_ptr;
	t_path	*path_ptr;

	ants_count = 1;
	algo_dbg(0, "Total ants : %d\n\n", ants);
	while (end->ant < ants)
	{
		first_ant = 1;
		node_ptr = route->paths->head;
		while (node_ptr)
		{
			path_ptr = get_path_from_node(node_ptr);
			move_ants(path_ptr, &ants_count, &first_ant);
			node_ptr = node_ptr->next;
		}
		ft_putchar('\n');
	}
}

static void	remove_non_solution_paths(t_route *route)
{
	t_node *node;
	t_node *node_next;
	t_path *path;

	node = route->paths->head;
	while (node)
	{
		node_next = node ? node->next : NULL;
		path = get_path_from_node(node);
		if (path->head->solution_len < 0)
		{
			ft_lstnode_remove(route->paths, node);
			ft_node_del(&node, (void*)&free_path_from_node);
		}
		node = node_next;
	}
}

int			print_ants(t_graph *graph, t_route *route)
{
	remove_non_solution_paths(route);
	set_paths_ants(route, graph->ants);
	print_ants_route(route, graph->ants, graph->end);
	return (0);
}
