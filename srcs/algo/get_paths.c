/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/06 18:03:08 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static int	local_exit(t_bfs *bfs_data, int retval)
{
	if (bfs_data)
		bfs_free(bfs_data);
	return (retval);
}

static int	append_next_rooms(t_bfs *bfs_data, t_path *path, t_vect *next_rooms)
{
	size_t i;
	t_path *new_path;
	t_room *room_ptr;

	i = 0;
	new_path = NULL;
	while (i < next_rooms->size)
	{
		room_ptr = ft_vector_get(next_rooms, i);
		if (i == next_rooms->size - 1)
			path_add_room(path, room_ptr);
		else
		{
			if (!(new_path = path_duplicate(path, bfs_data->paths_nbr + 1)))
				return (-1);
			path_mark_visited(new_path);
			path_add_room(new_path, room_ptr);
			bfs_add_path(bfs_data, &new_path);
		}
		if (room_is_end(room_ptr))
		{
			if (i == next_rooms->size - 1)
			{
				path_get_conflicts(path);
				if (bfs_add_end_path(bfs_data, &path) < 0)
					return (-1);
			}
			else
			{
				path_get_conflicts(new_path);
				if (bfs_add_end_path(bfs_data, &new_path) < 0)
					return (-1);
			}
		}
		i++;
	}
	return (0);
}

static t_vect *get_next_rooms_for_path(t_path *path)
{
	t_vect	*next_rooms;
	t_room	**last_room;
	t_room	*room_ptr;
	size_t	i;

	next_rooms = ft_vector_init(sizeof(t_room*), 0);
	last_room = path->head->content;
	i = 0;
	while (i < (*last_room)->links->size)
	{
		room_ptr = ft_vector_get((*last_room)->links, i);
		if (!room_is_start(room_ptr) && !room_has_id(room_ptr, path->id))
		{
			if (ft_vector_append(next_rooms, room_ptr) < 0)
			{
				ft_vector_free(next_rooms, (void*)&ft_bzero);
				return (NULL);
			}
		}
		i++;
	}
	return (next_rooms);
}

static int	get_next_depth(t_bfs *bfs_data)
{
	t_list *paths_ptr;
	t_path *path;
	t_vect *next_rooms;

	paths_ptr = bfs_data->all_paths;
	while (paths_ptr)
	{
		path = *(t_path**)paths_ptr->content;
		if (!path->is_stuck && !path->has_end)
		{
			if (!(next_rooms = get_next_rooms_for_path(path)))
				return (-1);
			if (next_rooms->size > 0)
			{
				if (append_next_rooms(bfs_data, path, next_rooms) < 0)
					return (-1);
			}
			else
				path->is_stuck = 1;
			ft_vector_free(next_rooms, (void*)&ft_bzero);
		}
		paths_ptr = paths_ptr->next;
	}
	return (0);
}

static int	bfs(t_bfs *bfs_data)
{
	int depth;

	depth = 0;
	while (/*paths_to_end->nbr_of_paths*/depth < 10)
	{
		if (get_next_depth(bfs_data) < 0)
			return (-1);
		depth++;
	}
	print_end_sets(bfs_data);
	return (depth);
}

static int	init_first_path(t_graph *graph, t_bfs *bfs_data)
{
	t_path	*start;

	start = NULL;
	if (!(start = init_new_path(1)))
		return (-1);
	if ((bfs_add_path(bfs_data, &start)) < 0)
		return (-1);
	if ((path_add_room(start, graph->start) < 0))
		return (-1);
	return (0);
}

int		get_paths(t_graph *graph)
{
	t_bfs		*bfs_data;

	if (!(bfs_data = init_bfs_data()))
		return (-1);
	if (init_first_path(graph, bfs_data) < 0)
		return (local_exit(bfs_data, 1));
	if (bfs(bfs_data) < 0)
		return (local_exit(bfs_data, 1));
	return (local_exit(bfs_data, 0));
}
