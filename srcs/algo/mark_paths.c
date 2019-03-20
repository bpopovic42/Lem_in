/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 03:00:14 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/20 20:00:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	erase_ptr(void ***ptr)
{
	t_room ***room_ptr;

	room_ptr = (t_room***)ptr;
	free(**room_ptr);
}

static void	mark_next_rooms(t_room *room, t_vect *next_rooms, int is_start)
{
	size_t	i;
	t_room	*ptr;

	i = 0;
	while (i < room->links->size)
	{
		ptr = ft_vector_get(room->links, i);
		if ((is_start && ptr->start_id < 0) || (!is_start && ptr->end_id < 0))
		{
			if (!room_is_end(ptr) && !room_is_start(ptr))
			{
				if (is_start && ptr->start_id < 0)
					ptr->start_id = room->start_id;
				else if (!is_start && ptr->end_id < 0)
					ptr->end_id = room->end_id;
				ft_vector_append(next_rooms, ptr);
			}
		}
		i++;
	}
}

static int	mark_rooms(t_vect *rooms, int is_start)
{
	size_t	i;
	t_room	*ptr;
	t_vect	*next_rooms;

	while (rooms->size)
	{
		if ((next_rooms = ft_vector_init(sizeof(t_room*), 0)))
		{
			i = 0;
			while (i < rooms->size)
			{
				ptr = ft_vector_get(rooms, i);
				mark_next_rooms(ptr, next_rooms, is_start);
				i++;
			}
			ft_vector_free(rooms, (void*)&erase_ptr);
			rooms = next_rooms;
		}
		else
			return (-1);
	}
	return (0);
}

static void mark_path_head(t_path *path, int path_id, int is_start)
{
	if (is_start)
	path->head->start_id = path_id;
	else
		path->head->end_id = path_id;
	path->path_id = path_id;
}

int			mark_paths(t_list *paths_list, int is_start)
{
	size_t	path_id;
	t_node	*list_ptr;
	t_vect	*rooms;

	path_id = 0;
	list_ptr = paths_list->head;
	if (!(rooms = ft_vector_init(sizeof(t_room*), 0)))
		return (-1);
	while (list_ptr)
	{
		if (ft_vector_append(rooms, (*(t_path**)list_ptr->data)->head) >= 0)
		{
			mark_path_head(*(t_path**)list_ptr->data, path_id, is_start);
			list_ptr = list_ptr->next;
			path_id++;
		}
		else
		{
			ft_vector_free(rooms, (void*)&erase_ptr);
			return (-1);
		}
	}
	if (mark_rooms(rooms, is_start) < 0)
		return (-1);
	return (0);
}
