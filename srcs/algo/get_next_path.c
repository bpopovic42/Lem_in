/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 01:40:52 by bopopovi          #+#    #+#             */
/*   Updated: 2019/04/03 06:29:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*duplicate_path(t_path *path)
{
	t_path	*path_dup;
	t_list	*rooms_dup;

	if (!(rooms_dup = ft_lstdup(path->rooms)))
		return (NULL);
	if (!(path_dup = ft_memalloc(sizeof(*path_dup))))
		return (NULL);
	path_dup->length = path->length;
	path_dup->id = path->id; //
	path_dup->rooms = rooms_dup;
	return (path_dup);
}

static int		tail_is_not_end(t_path *path)
{
	t_room *ptr;

	ptr = NULL;
	if (path)
	{
		if (path->rooms)
		{
			if (path->rooms->tail && path->rooms->tail->data)
			{
				ptr = *(t_room**)path->rooms->tail->data;
				if (ptr->command)
				{
					if (!ft_strcmp("##end", ptr->command))
						return (0);
				}
			}
		}
	}
	return (1);
}

static int		is_not_visited(t_room *room, t_path *path)
{
	t_node *tmp;
	t_room *ptr;

	tmp = path->rooms->head;
	while (tmp)
	{
		ptr = *(t_room**)tmp->data;
		if (!ft_strcmp(room->name, ptr->name))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static int		get_new_paths(t_list *bfs_paths, t_path *base_path)
{
	t_room	*path_tail;
	t_room	*new_tail;
	t_path	*new_path;
	size_t	i;

	path_tail = *(t_room**)ft_lstget_tail_data(base_path->rooms);
	new_tail = NULL;
	i = 0;
	while (i < path_tail->links->size)
	{
		new_tail = ft_vector_get(path_tail->links, i);
		if (is_not_visited(new_tail, base_path))
		{
			if (!(new_path = duplicate_path(base_path)))
				return (0);
			if (ft_lstpush_back_data(new_path->rooms, &new_tail, sizeof(new_tail)) < 0)
				return (-1);
			if (ft_lstadd_data(bfs_paths, &new_path, sizeof(new_path)) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

int			get_next_path(size_t *depth, t_list *bfs_paths, t_list *recorded_paths)
{
	t_path	*path;

	while (bfs_paths->size > 0)
	{
		path = *(t_path**)ft_lstpop_data(bfs_paths);
		get_new_paths(bfs_paths, path);
		//ft_lstdel(&path);
		(*depth)++;
		if (tail_is_not_end(path))
			path = NULL;//ft_lstdel(&path);
		else
			break ;
	}
	if (path)
	{
		if (ft_lstadd_data(recorded_paths, &path, sizeof(path)) < 0)
			return (-1);
		return (1);
	}
	return (0);
}
