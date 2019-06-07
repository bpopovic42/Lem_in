/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_route.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:39:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 20:24:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static void tmp_print_rooms(t_room *src)
{
	t_room *ptr;

	ptr = src;
	while (ptr && !room_is_end(ptr))
	{
		ft_printf("%s ", ptr->name);
		ptr = ptr->to;
	}
	ft_putchar('\n');
}

void	tmp_print_paths(t_list *paths)
{
	t_node *node_ptr;
	t_path *path_ptr;

	node_ptr = paths->head;
	while (node_ptr)
	{
		path_ptr = get_path_from_node(node_ptr);
		if (path_ptr->final_length >= 0)
		{
			ft_printf("Path of length %d :\n", path_ptr->final_length);
			tmp_print_rooms(path_ptr->head);
		}
		node_ptr = node_ptr->next;
	}
}

int		find_best_route(t_graph *graph, t_route *route, t_queue *bfs)
{
	t_path	*first_path;
	t_node	*node_ptr;
	bool	break_flag;

	first_path = NULL;
	node_ptr = route->paths->head;
	break_flag = false;
	while ((first_path = get_path_from_node(node_ptr)))
	{
		ft_printf(" [ 1st path is %s ]\n", first_path->head->name);
		reweight_graph(graph, route->paths, bfs);
		mark_path(first_path);
		mark_next_paths(graph, route->paths, bfs);
		tmp_print_paths(route->paths);
		update_score(graph, route);
		if (!break_flag || break_link(first_path) == 0)
			node_ptr = node_ptr->next;
		if (!node_ptr && !break_flag)
		{
			break_flag = true;
			node_ptr = route->paths->head;
		}
		clean_graph(graph);
		ft_putchar('\n');
	}
	return (0);
}
