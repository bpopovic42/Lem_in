/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/13 20:07:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

void	free_file(t_file *file)
{
	if (file)
	{
		if (file->data)
			ft_strdel(&file->data);
		ft_bzero(file, sizeof(*file));
		free(file);
	}
}

int		init_file(t_file **file)
{
	if (!(*file = ft_memalloc(sizeof(**file))))
		return (-1);
	if (!((*file)->data = ft_strnew(LMN_BUFF_SIZE + 1)))
		return (-1);
	(*file)->capacity = LMN_BUFF_SIZE + 1;
	(*file)->size = 0;
	return (0);
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

int		main(void)
{
	t_file	*file;
	t_graph	graph;

	file = NULL;
	if (init_graph(&graph) < 0)
		return (1);
	if (init_file(&file) < 0)
		return (1);
	if (parse_input(&graph.ants, &graph, file) != 0)
		return (local_exit(&graph, file, 1));
	get_best_paths(&graph);
	restore_solution_len(graph.start);
	print_ants(graph.ants, graph.start, graph.end);
	return (local_exit(&graph, file, 0));
}
