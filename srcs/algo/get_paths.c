/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/04 16:23:25 by bopopovi         ###   ########.fr       */
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

static void		set_ptr_null(t_room **room, size_t data_size)
{
	ft_bzero(room, data_size);
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
				ft_vector_free(next_rooms, (void*)&set_ptr_null);
				return (NULL);
			}
		}
		i++;
	}
	return (next_rooms);
}

static int	append_next_rooms(t_set *all_paths, t_path *path, t_vect *next_rooms)
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
			if (!(new_path = path_duplicate(path, all_paths->nbr_of_paths + 1)))
				return (-1);
			path_mark_visited(new_path);
			path_add_room(new_path, room_ptr);
			set_add_path(all_paths, new_path);
		}
		i++;
	}
	return (0);
}

static int	get_next_depth(t_set *all_paths)
{
	t_list *paths_ptr;
	t_path *path;
	t_vect *next_rooms;

	paths_ptr = all_paths->paths;
	while (paths_ptr)
	{
		path = *(t_path**)paths_ptr->content;
		if (!path->is_stuck && !path->has_end)
		{
			if (!(next_rooms = get_next_rooms_for_path(path)))
				return (-1);
			if (next_rooms->size > 0)
				append_next_rooms(all_paths, path, next_rooms);
			else
				path->is_stuck = 1;
			ft_vector_free(next_rooms, (void*)&set_ptr_null);
		}
		paths_ptr = paths_ptr->next;
	}
	return (0);
}

static int	bfs(t_set *all_paths)
{
	int depth;

	depth = 0;
	while (/*paths_to_end->nbr_of_paths*/depth < 10)
	{
		if (get_next_depth(all_paths) < 0)
			return (-1);
		depth++;
	}
	print_set(all_paths);
	return (depth);
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
		if (bfs(all_paths) < 0)
		{
			set_free(all_paths);
			return (-1);
		}
	}
	set_free(all_paths);
	return (0);
}
