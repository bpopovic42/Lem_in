/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/26 21:17:35 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void	print_path(t_path *path)
{
	t_dlist *ptr;

	if (path)
	{
		ptr = path->head;
		while (ptr)
		{
			ft_putendl((*((t_room**)ptr->content))->name);
			ptr = ptr->next;
		}
	}
}

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

t_path	*init_new_path(t_dlist *path, size_t path_length)
{
	t_path *new_path;

	if (!(new_path = malloc(sizeof(*new_path))))
		return (NULL);
	new_path->length = path_length;
	new_path->head = path;
	return (new_path);
}

t_set		*init_new_set(void)
{
	t_set *new_set;

	if (!(new_set = malloc(sizeof(*new_set))))
		return (NULL);
	new_set->nbr_of_paths = 0;
	new_set->biggest = 0;
	new_set->lowest = 0;
	new_set->diff = 0;
	new_set->paths = NULL;
	return (new_set);
}

int		add_new_path(t_set *path_set, t_dlist *path, size_t path_length)
{
	t_path		*new_path;

	if (!(new_path = init_new_path(path, path_length)))
		return (-1);
	if (ft_lstadd_data(&path_set->paths, &new_path, sizeof(new_path)) < 0)
		return (-1);
	return (0);
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
	if (add_new_path(all_paths, start, 1) < 0)
		return (1);
	bfs(all_paths, paths_to_end);
	return (0);
}
