/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/09 21:14:26 by bopopovi         ###   ########.fr       */
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

void	print_solution_path(t_room *src)
{
	t_room *ptr;

	ptr = src;
	//ft_printf("PATH [%d]\n", src->pid);
	while (ptr)
	{
		if (!room_is_end(ptr))
			ft_putstr(ptr->name);
		if (ptr->solution_to != NULL)
			ft_putchar('\n');
		ptr = ptr->solution_to;
	}
	ft_putchar('\n');
}

void	print_solution(t_graph *graph)
{
	t_room *room_ptr;
	t_node *node_ptr;

	node_ptr = graph->start->links->head;
	room_ptr = NULL;
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->solution_to != NULL)
			print_solution_path(room_ptr);
		node_ptr = node_ptr->next;
	}
}

int		get_output_data(t_output *out, t_room *start)
{
	t_node *node_ptr;
	t_room *room_ptr;

	out->longest_path_len = -1;
	out->nbr_of_paths = 0;
	room_ptr = NULL;
	node_ptr = start->links->head;
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->solution_to)
		{
			out->nbr_of_paths++;
			if (room_ptr->solution_len > out->longest_path_len)
				out->longest_path_len = room_ptr->solution_len;
		}
		node_ptr = node_ptr->next;
	}
	return (0);
}

int		get_paths(t_output *out, int ants, t_room *start)
{
	t_node	*node_ptr;
	t_room	*room_ptr;
	int		surplus;
	int		div_ants;
	int		i;
	int		diff;

	room_ptr = NULL;
	diff = 0;
	i = 0;
	surplus = 0;
	node_ptr = start->links->head;
	if (!(out->paths = ft_memalloc(sizeof(t_path*) * out->nbr_of_paths)))
		return (-1);
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->solution_to)
		{
			if (!(out->paths[i] = ft_memalloc(sizeof(t_path))))
				return (-1);
			out->paths[i]->last_ant = NULL;
			out->paths[i]->src = room_ptr;
			out->paths[i]->ants = out->longest_path_len - room_ptr->solution_len;
			diff += out->paths[i]->ants;
			i++;
		}
		node_ptr = node_ptr->next;
	}
	//ft_printf("Diff %d\n", diff);
	div_ants = (ants - diff) / out->nbr_of_paths;
	surplus = (ants - diff) % out->nbr_of_paths;
	i = 0;
	while (i < out->nbr_of_paths)
	{
		out->paths[i]->ants += div_ants;
		if (surplus)
		{
			out->paths[i]->ants += 1;
			surplus--;
		}
		//ft_printf("for path %s of len %d, %d ants\n", out->paths[i]->src->name, out->paths[i]->src->solution_len, out->paths[i]->ants);
		i++;
	}
	return (0);
}

void	advance_path(t_path *path, int *ants_count)
{
	t_room *ptr;

	if (!path->last_ant)
		path->last_ant = path->src;
	ptr = path->last_ant;
	//ft_printf("from %s %d\n", ptr->name, path->ants);
	while (ptr && !room_is_start(ptr))
	{
		if (ptr->solution_from && ptr->solution_from->ant == 0 && ptr != path->src)
		{
			//exit(0);
			;
		}
		if (room_is_end(ptr->solution_to) && ptr->ant != 0)
		{
			ft_printf("L%d-%s ", ptr->ant, ptr->solution_to->name);
			ptr->solution_to->ant++;
			ptr->ant = 0;
		}
		else
		{
			if (ptr == path->src)
			{
				if (path->ants > 0)
				{
					ptr->ant = (*ants_count)++;
					path->ants--;
					ft_printf("L%d-%s ", ptr->ant, ptr->name);
				}
				else
					break;
			}
			else if (ptr->solution_from && ptr->solution_from->ant > 0)
			{
				ft_printf("L%d-%s ", ptr->solution_from->ant, ptr->name);
				ptr->ant = ptr->solution_from->ant;
				ptr->solution_from->ant = 0;
			}
			ptr = ptr->solution_from;
		}
	}
	if (!room_is_end(path->last_ant->solution_to))
		path->last_ant = path->last_ant->solution_to;
}

void	print_ants_route(t_output *out, int ants, t_room *end)
{
	int i;
	int ants_count;

	ants_count = 1;
	while (end->ant < ants)
	{
		i = 0;
		while (i < out->nbr_of_paths)
		{
			advance_path(out->paths[i], &ants_count);
			i++;
		}
		ft_putchar('\n');
	}
}

int		print_ants(int ants, t_room *start, t_room *end)
{
	t_output *out;

	if (!(out = ft_memalloc(sizeof(*out))))
		return (-1);
	if (get_output_data(out, start) < 0)
		return (-1);
	get_paths(out, ants, start);
	(void)end;
	//print_ants_route(out, ants, end);
	return (0);
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
		//ft_printf("%s ", ptr->name);
		ptr = ptr->solution_to;
	}
	//ft_putchar('\n');
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
		{
			get_path_len(room_ptr);
			ft_printf("path %s of final len %d\n", room_ptr->name, room_ptr->solution_len);
		}
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
	//print_solution(&graph);
	return (local_exit(&graph, file, 0));
}
