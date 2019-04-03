/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best_path_combination.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 01:40:43 by bopopovi          #+#    #+#             */
/*   Updated: 2019/04/03 05:46:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*init_bfs_paths(t_room *initial_room)
{
	t_list *paths_holder;
	t_path *new_path;
	t_list *rooms;

	if (!(rooms = ft_lstnew()))
		return (NULL);
	if (ft_lstadd_data(rooms, &initial_room, sizeof(initial_room)) < 0)
		return (NULL);
	if (!(new_path = ft_memalloc(sizeof(*new_path))))
		return (NULL);
	new_path->length = 0;
	new_path->id = 0;
	new_path->rooms = rooms;
	if (!(paths_holder = ft_lstnew()))
		return (NULL);
	if (ft_lstadd_data(paths_holder, &new_path, sizeof(new_path)) < 0)
		return (NULL);
	return (paths_holder);
}

static void		print_path(t_node *node)
{
	t_path *path;
	t_node *ptr;

	path = (*(t_path**)node->data);
	ptr = path->rooms->head;
	while (ptr)
	{
		ft_putendl((*(t_room**)ptr->data)->name);
		ptr = ptr->next;
	}
	ft_putchar('\n');
}

int				find_best_path_combination(int ants, t_graph *graph)
{
	size_t	depth_limit;
	size_t	depth;
	t_list	*paths_list;
	t_list	*bfs_paths;

	(void)ants;
	depth_limit = 500;
	depth = 0;
	if (!(paths_list = ft_lstnew()))
		return (-1);
	if (!(bfs_paths = init_bfs_paths(graph->start)))
		return (-1);
	while ((get_next_path(&depth, bfs_paths, paths_list)) > 0 && depth < depth_limit)
	{
		;
	}
	ft_lstiter(paths_list, &print_path);
	return (0);
}
