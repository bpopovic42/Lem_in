/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/01 02:11:34 by bopopovi         ###   ########.fr       */
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

static int	room_has_id(t_room *room, int id)
{
	t_list *id_ptr;

	if (room->path_ids)
	{
		id_ptr = room->path_ids;
		while (id_ptr)
		{
			if (id == (int)id_ptr->content)
				return (1);
			id_ptr = id_ptr->next;
		}
	}
	return (0);
}

static t_vect *get_next_rooms_for_path(t_path **path)
{
	// ADD IS STUCK AND IS END SOMEWHERE IN THIS FUNCTION ?
	t_vect	*next_rooms;
	t_room	**last_room;
	t_room	*room_ptr;
	size_t		i;

	next_rooms = ft_vector_init(sizeof(t_room*), 0);
	last_room = (*path)->head->content;
	i = 0;
	while (i < (*last_room)->links->size)
	{
		room_ptr = ft_vector_get((*last_room)->links, i);
		if (!room_ptr->command || ft_strcmp("##start", room_ptr->command))
		{
			if (!room_has_id(room_ptr, (*path)->id))
			{
				ft_vector_append(next_rooms, room_ptr); // Need protection !
			}
		}
		i++;
	}
	return (next_rooms);
}

static int	append_next_rooms(t_set *all_paths, t_path **path, t_vect *next_rooms)
{
	size_t i;
	t_path *new_path;
	t_room *room_ptr;

	i = 0;
	new_path = NULL;
	while (i < next_rooms->size)
	{
		room_ptr = ft_vector_get(next_rooms, i);
		if (next_rooms->size - i == 1)
		{
			path_add_room(*path, room_ptr);
			if (room_ptr->command && !ft_strcmp("##end", room_ptr->command))
				path_set_end(*path);
		}
		else
		{
			if (!(new_path = path_duplicate(*path, all_paths->nbr_of_paths + 1)))
				return (-1);
			path_add_room(new_path, room_ptr);
			set_add_path(all_paths, new_path);
			if (room_ptr->command && !ft_strcmp("##end", room_ptr->command))
				path_set_end(new_path);
		}
		i++;
	}
	return (0);
}

static void tmp_erase_room_ptr(t_room **room)
{
	ft_bzero(*room, sizeof(*room));
}

static void	get_next_depth(t_set *all_paths)
{
	t_list *paths_ptr;
	t_vect *next_rooms;

	paths_ptr = all_paths->paths;
	while (paths_ptr)
	{
		if (!path_is_stuck(*(t_path**)paths_ptr->content) && !path_has_end(*(t_path**)paths_ptr->content))
		{
			next_rooms = get_next_rooms_for_path(paths_ptr->content);
			if (next_rooms->size > 0)
			{
				append_next_rooms(all_paths, paths_ptr->content, next_rooms);
			}
			else
				path_set_stuck(*(t_path**)paths_ptr->content);
			ft_vector_free(next_rooms, (void*)&tmp_erase_room_ptr);// Get right free function
		}
		paths_ptr = paths_ptr->next;
	}
}

static void	bfs(t_set *all_paths)
{
	int depth;

	depth = 0;
	while (/*paths_to_end->nbr_of_paths*/depth < 4)
	{
		get_next_depth(all_paths);
		//get_next_rooms(&paths, final_paths);
		depth++;
	}
	print_set(all_paths);
	//print_final_paths(final_paths);
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
