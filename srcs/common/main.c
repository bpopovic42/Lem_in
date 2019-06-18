/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 16:36:31 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	local_exit(t_graph *graph, t_file *file, t_route *route, int retval)
{
	free_graph(graph);
	free_file(file);
	free_route(route);
	return (retval);
}

static int	init_lem_in_data(t_graph *graph, t_file *file, t_route *route)
{
	ft_bzero(graph, sizeof(*graph));
	ft_bzero(file, sizeof(*file));
	ft_bzero(route, sizeof(*route));
	if (init_graph(graph) < 0)
		return (-1);
	if (init_file(file) < 0)
		return (-1);
	if (init_route(route) < 0)
		return (-1);
	return (0);
}

static int	graph_has_solution(t_route *route)
{
	if (route->paths->size <= 0)
	{
		lemin_perror(ENOPATH, ENOPATH_MSG);
		return (0);
	}
	return (1);
}

int			main(void)
{
	t_file		file;
	t_graph		graph;
	t_route		route;

	if (init_lem_in_data(&graph, &file, &route) < 0)
		return (local_exit(&graph, &file, &route, 1));
	if (parse_input(&graph.ants, &graph, &file) != 0)
		return (local_exit(&graph, &file, &route, 1));
	if (get_best_route(&graph, &route) < 0)
		return (local_exit(&graph, &file, &route, 1));
	if (!graph_has_solution(&route))
		return (local_exit(&graph, &file, &route, 1));
	print_dbg(0, "Final score : %d\n", route.score->output_size);
	ft_putendl(file.data);
	if (print_ants(&graph, &route) != 0)
		return (local_exit(&graph, &file, &route, 1));
	return (local_exit(&graph, &file, &route, 0));
}
