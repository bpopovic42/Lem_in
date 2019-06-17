/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/17 17:27:06 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{ return (a * (1 - 2 * (a < 0)));
}

__attribute__((unused)) void tmp_print_rooms(t_room *src)
{
	t_room *ptr;

	ptr = src;
	while (ptr && !room_is_end(ptr))
	{
		ft_printf("%s ", ptr->name);
		ptr = ptr->solution_to;
	}
	ft_putchar('\n');
}

__attribute__((unused)) void tmp_print_paths_rooms(t_list *paths)
{
	t_node *ptr;
	t_path *path;

	ptr = paths->head;
	while (ptr)
	{
		path = *(t_path**)ptr->data;
		if (path->head->is_solution > 0)
		{
			tmp_print_rooms(path->head);
		}
		ptr = ptr->next;
	}
}

static int		local_exit(t_graph *graph, t_file *file, t_route *route, int retval)
{
	free_graph(graph);
	free_file(file);
	free_route(route);
	return (retval);
}

int		initialize_lem_in_data(t_graph *graph, t_file *file, t_route *route)
{
	if (init_graph(graph) < 0)
		return (-1);
	if (init_file(file) < 0)
		return (-1);
	if (init_route(route) < 0)
		return (-1);
	return (0);
}

int		main(void)
{
	t_file		file;
	t_graph		graph;
	t_route		route;

	if (initialize_lem_in_data(&graph, &file, &route) < 0)
		return (local_exit(&graph, &file, &route, 1));
	if (parse_input(&graph.ants, &graph, &file) != 0)
		return (local_exit(&graph, &file, &route, 1));
	if (get_best_route(&graph, &route) < 0)
		return (local_exit(&graph, &file, &route, 1));
	if (route.paths->size <= 0)
	{
		lemin_perror(ENOPATH, ENOPATH_MSG);
		return (local_exit(&graph, &file, &route, 1));
	}
	else
	{
		print_dbg(0, "Final score : %d\n", route.score->output_size);
		ft_putendl(file.data);
		if (print_ants(&graph, &route) != 0)
			return (local_exit(&graph, &file, &route, 1));
	}
	return (local_exit(&graph, &file, &route, 0));
}
