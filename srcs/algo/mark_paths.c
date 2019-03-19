/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 03:00:14 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/19 15:11:38 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*static void	erase_ptr(void **ptr)
{
	t_room **room_ptr;

	room_ptr = (t_room**)ptr;
	free(*ptr);
}*/

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

	i = 0;
	while (rooms->size)
	{
		if (!(next_rooms = ft_vector_init(sizeof(t_room*), 0)))
			return (-1);
		while (i < rooms->size)
		{
			ptr = ft_vector_get(rooms, i);
			mark_next_rooms(ptr, next_rooms, is_start);
			i++;
		}
		i = 0;
		//ft_vector_free(rooms, (void*)&erase_ptr);
		rooms = next_rooms;
	}
	return (0);
}

int			mark_paths(t_list *source, int is_start)
{
	size_t	path_id;
	t_vect	*rooms;
	t_node	*ptr;

	path_id = 0;
	ptr = source->head;
	if (!(rooms = ft_vector_init(sizeof(t_room*), 0)))
		return (-1);
	while (ptr)
	{
		if (is_start)
			((t_room*)(*(t_tmp**)ptr->data)->room)->start_id = path_id;
		else
			((t_room*)(*(t_tmp**)ptr->data)->room)->end_id = path_id;
		if (ft_vector_append(rooms, (*(t_tmp**)ptr->data)->room) < 0)
			return (-1);
		(*(t_tmp**)ptr->data)->path_id = path_id;
		path_id++;
		ptr = ptr->next;
	}
	mark_rooms(rooms, is_start);
	return (0);
}
