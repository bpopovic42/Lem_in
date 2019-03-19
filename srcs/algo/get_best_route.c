/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:26:43 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/19 15:19:21 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void	print_next_rooms(t_room *target, int from_start)
{
	size_t	i;
	int		*target_depth;
	t_room *ptr;

	i = 0;
	while (i < target->links->size)
	{
		ptr = ft_vector_get(target->links, i);
		target_depth = from_start ? &ptr->end_len : &ptr->start_len;
		ft_printf("Room '%s' depth = %d\n", ptr->name, *target_depth);
		i++;
	}
}

static void tmp_print(t_list *path_list)
{
	t_tmp *tmp;
	t_node *ptr;

	ptr = path_list->head;
	while (ptr)
	{
		tmp = *(t_tmp**)ptr->data;
		ft_printf("Path %s of size %d\n", tmp->room->name, tmp->size);
		ptr = ptr->next;
	}
	ft_putchar('\n');
}

static int	cmp_paths(void *a, void *b)
{
	t_tmp *path_a;
	t_tmp *path_b;

	path_a = (t_tmp*)a;
	path_b = (t_tmp*)b;
	return (path_a->size < path_b->size);
}

#include "ft_printf.h"

static void array_print(int **matrix, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			ft_printf("| %d |", matrix[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int		get_best_route(t_graph *graph)
{
	t_list	*start_paths;
	t_list	*end_paths;
	int		**paths_matrix;

	if (weight_graph(graph->end, 0) < 0)
		return (-1);
	print_next_rooms(graph->start, 1);
	ft_putchar('\n');
	if (weight_graph(graph->start, 1) < 0)
		return (-1);
	print_next_rooms(graph->end, 0);

	if (!(start_paths = get_starting_paths(graph->start, 1)))
		return (-1);
	if (!(end_paths = get_starting_paths(graph->end, 0)))
		return (-1);

	ft_lstsort(start_paths, &cmp_paths);
	ft_lstsort(end_paths, &cmp_paths);
	tmp_print(start_paths);
	tmp_print(end_paths);

	mark_paths(start_paths, 1);
	mark_paths(end_paths, 0);

	paths_matrix = get_paths_matrix(start_paths, end_paths);
	array_print(paths_matrix, start_paths->size, end_paths->size);
	return (0);
}
