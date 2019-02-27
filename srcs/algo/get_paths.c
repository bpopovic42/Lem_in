/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/27 19:12:07 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void	bfs(t_set *all_paths, t_set *paths_to_end)
{
	int depth;

	depth = 0;
	(void)all_paths;
	(void)paths_to_end;
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
	t_set		*paths_to_end;
	t_dlist		*start;

	(void)graph;
	if (!(all_paths = init_new_set()))
		return (1);
	if (!(paths_to_end = init_new_set()))
		return (1);
	if (!(start = ft_dlstnew(&graph->start, sizeof(graph->start))))
		return (1);
	if (set_add_new_path(all_paths, start, 1) < 0)
		return (1);
	bfs(all_paths, paths_to_end);
	set_free(all_paths);
	set_free(paths_to_end);
	return (0);
}
