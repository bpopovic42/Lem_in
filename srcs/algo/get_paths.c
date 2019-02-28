/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/28 19:12:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static int	init_first_path(t_graph *graph, t_set **all_paths)
{
	t_path		*start;

	start = NULL;
	if (!(start = init_new_path(1)))
		return (-1);
	if ((set_add_path(*all_paths, start)) < 0)
		return (-1);
	if ((set_add_room_to_path(*all_paths, 1, graph->start) < 0))
		return (-1);
	return (0);
}

static void	bfs(t_set *all_paths)
{
	int depth;

	depth = 0;
	print_path(*(t_path**)all_paths->paths->content);
	/*while (paths_to_end->nbr_of_paths < 3)
	{
		mark_visited(all_paths);
		get_next_rooms(&paths, final_paths);
		depth++;
	}
	print_final_paths(final_paths);*/
}

int		get_paths(t_graph *graph)
{
	t_set		*all_paths;

	if (!(all_paths = init_new_set(1)))
		return (1);
	if (init_first_path(graph, &all_paths) < 0)
	{
		set_free(all_paths);
		return (1);
	}
	else
	{
		bfs(all_paths);
	}
	set_free(all_paths);
	return (0);
}
