/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:26:43 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/20 21:28:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	erase_ptr(void ***ptr)
{
	t_room ***room_ptr;

	room_ptr = (t_room***)ptr;
	free(**room_ptr);
}

static int	local_exit(int **paths_matrix, t_list *start_paths, t_list *end_paths, int status)
{
	(void)paths_matrix;
	//if (paths_matrix)
		//ft_array_del(&paths_matrix);
	if (start_paths)
		ft_lstdel(start_paths, (void*)&erase_ptr);
	if (end_paths)
		ft_lstdel(end_paths, (void*)&erase_ptr);
	return (status);
}

static int	cmp_paths(void *a, void *b)
{
	t_path *path_a;
	t_path *path_b;

	path_a = *(t_path**)a;
	path_b = *(t_path**)b;
	return (path_a->size < path_b->size);
}

int		get_best_route(t_graph *graph)
{
	t_list	*start_paths;
	t_list	*end_paths;
	int		**paths_matrix;

	if (weight_graph(graph->end) < 0)
		return (-1);
	//dbg_print_next_rooms(graph->start, 1);
	if (weight_graph(graph->start) < 0)
		return (-1);
	//dbg_print_next_rooms(graph->end, 0);

	if (!(start_paths = get_paths(graph->start, 1)))
		return (local_exit(NULL, start_paths, NULL, -1));
	if (!(end_paths = get_paths(graph->end, 0)))
		return (local_exit(NULL, start_paths, end_paths, -1));

	ft_lstsort(start_paths, &cmp_paths);
	ft_lstsort(end_paths, &cmp_paths);
	//dbg_print_paths(start_paths);
	//dbg_print_paths(end_paths);

	mark_paths(start_paths, 1);
	mark_paths(end_paths, 0);

	paths_matrix = get_paths_matrix(start_paths, end_paths);
	dbg_array_print(paths_matrix, start_paths->size, end_paths->size);
	return (local_exit(paths_matrix, start_paths, end_paths, 0));
}
