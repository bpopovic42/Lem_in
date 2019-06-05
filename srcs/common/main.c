/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 13:33:02 by bopopovi         ###   ########.fr       */
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

static int		local_exit(t_graph *graph, t_file *file, t_solution *solution, int retval)
{
	free_graph(graph);
	free_file(file);
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

void	restore_best_marks(t_room *start)
{
	t_node *ptr;
	t_room *room_ptr;

	ptr = start->links->head;
	room_ptr = NULL;
	//ft_printf("FINAL SOLUTION :\n");
	while (ptr)
	{
		room_ptr = *(t_room**)ptr->data;
		if (room_ptr->is_solution)
		{
			get_path_len(room_ptr);
			//ft_printf("%s\n", room_ptr->name);
		}
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

	if (initialize_lem_in_data(&graph, &file, &solution) < 0)
		return (local_exit(&graph, &file, &solution, 1));
	if (parse_input(&graph.ants, &graph, &file) == 0)
	{
		if (mark_best_paths(&graph, &solution) == 0)
		{
			restore_best_marks(graph.start);
			if (print_ants(graph.ants, graph.start, graph.end) == 0)
				return (local_exit(&graph, &file, &solution, 0));
		}
	}
	return (local_exit(&graph, &file, &solution, 1));
	//tmp_print_paths_rooms(graph.start);
}
