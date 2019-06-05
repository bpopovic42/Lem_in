/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 19:38:57 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

__attribute__((unused)) void tmp_print_rooms(t_room *src)
{
	t_room *ptr;

	ptr = src;
	while (ptr && !room_is_end(ptr))
	{
		ft_printf("%s\n", ptr->name);
		ptr = ptr->solution_to;
	}
	ft_putchar('\n');
}

__attribute__((unused)) void tmp_print_paths_rooms(t_room *start)
{
	t_node *ptr;
	t_room *room;

	ptr = start->links->head;
	while (ptr)
	{
		room = *(t_room**)ptr->data;
		if (room->solution_len >= 0)
		{
			tmp_print_rooms(room);
		}
		ptr = ptr->next;
	}
	exit(0);
}

static int		local_exit(t_graph *graph, t_file *file, t_queue *bfs, t_solution *solution, int retval)
{
	free_graph(graph);
	free_file(file);
	if (bfs)
		free_bfs_queue(&bfs);
	ft_bzero(solution, sizeof(*solution));
	return (retval);
}

void	get_path_len(t_room *src)
{
	size_t len;
	t_room *ptr;

	ptr = src;
	len = 0;
	while (ptr && !room_is_end(ptr))
	{
		len++;
		ptr = ptr->solution_to;
	}
	src->solution_len = len;
}

void	restore_best_solution(t_list *paths)
{
	t_node *ptr;
	t_node *tmp;
	t_path *path_ptr;

	ptr = paths->head;
	path_ptr = NULL;
	//ft_printf("FINAL SOLUTION :\n");
	while (ptr)
	{
		path_ptr = *(t_path**)ptr->data;
		tmp = ptr->next;
		if (path_ptr->head->is_solution)
		{
			ft_putendl("YAAAAAAAAAAAAY");
			get_path_len(path_ptr->head);
			//ft_printf("%s\n", room_ptr->name);
		}
		else if (room_is_end(path_ptr->head))
			path_ptr->head->solution_len = 0;
		else
			ft_lstnode_remove(paths, ptr);
		ptr = tmp;
	}
}

void	init_solution(t_solution *solution)
{
	ft_bzero(solution, sizeof(*solution));
	solution->value = -1;
}

int		initialize_lem_in_data(t_graph *graph, t_file *file, t_solution *solution)
{
	if (init_graph(graph) < 0)
		return (-1);
	if (init_file(file) < 0)
		return (-1);
	init_solution(solution);
	return (0);
}

int		main(void)
{
	t_file		file;
	t_graph		graph;
	t_solution	solution;
	t_list		paths;
	t_queue		*bfs;

	bfs = NULL;
	if (initialize_lem_in_data(&graph, &file, &solution) < 0)
		return (local_exit(&graph, &file, bfs, &solution, 1));
	if (parse_input(&graph.ants, &graph, &file) == 0)
	{
		if (init_bfs_queue(&bfs, graph.nbr_of_rooms) < 0)
			return (local_exit(&graph, &file, bfs, &solution, 1));
		if (get_initial_paths(&graph, bfs, &paths) <= 0)
			return (local_exit(&graph, &file, bfs, &solution, 0));//
		//print_file
		if (mark_best_paths(&graph, bfs, &paths, &solution) == 0)
		{
			restore_best_solution(&paths);
			if (print_ants(graph.ants, &paths, graph.end) == 0)
				return (local_exit(&graph, &file, bfs, &solution, 0));
		}
	}
	return (local_exit(&graph, &file, bfs, &solution, 1));
	//tmp_print_paths_rooms(graph.start);
}
