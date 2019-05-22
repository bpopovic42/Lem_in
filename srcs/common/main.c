/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/22 17:03:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

static int		local_exit(t_graph *graph, t_file *file, int retval)
{
	free_graph(graph);
	free_file(file);
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

void	restore_solution_len(t_room *start)
{
	t_node *ptr;
	t_room *room_ptr;

	ptr = start->links->head;
	room_ptr = NULL;
	while (ptr)
	{
		room_ptr = *(t_room**)ptr->data;
		if (room_ptr->solution_to)
			get_path_len(room_ptr);
		else if (room_is_end(room_ptr))
			room_ptr->solution_len = 0;
		ptr = ptr->next;
	}
}

void	init_solution(t_solution *solution)
{
	ft_bzero(solution, sizeof(*solution));
	solution->value = -1;
}

void tmp_print_rooms(t_room *src)
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

void tmp_print_paths_rooms(t_room *start)
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
}

int		main(void)
{
	t_file		*file;
	t_graph		graph;
	t_solution	solution;

	file = NULL;
	if (init_graph(&graph) < 0)
		return (1);
	if (init_file(&file) < 0)
		return (1);
	init_solution(&solution);
	if (parse_input(&graph.ants, &graph, file) != 0)
		return (local_exit(&graph, file, 1));
	if (get_best_paths(&graph, &solution))
		return (local_exit(&graph, file, 1));
	restore_solution_len(graph.start);
	tmp_print_paths_rooms(graph.start);
	exit(0);
	if (print_ants(graph.ants, graph.start, graph.end))
		return (local_exit(&graph, file, 0));
	return (local_exit(&graph, file, 0));
}
