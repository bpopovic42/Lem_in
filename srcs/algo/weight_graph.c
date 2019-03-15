/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:00:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/15 21:03:11 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void	set_ptr_null(void **ptr, size_t ptr_size)
{
	t_room **room_ptr;

	room_ptr = (t_room**)ptr;
	ft_bzero(room_ptr, ptr_size);
}

static int		local_exit(t_vect *rooms, t_vect *next, int exit_code)
{
	if (rooms)
		ft_vector_free(rooms, &set_ptr_null);
	if (next)
		ft_vector_free(next, &set_ptr_null);
	return (exit_code);
}

static int	get_next_rooms(int depth, t_vect *next_rooms, t_room *room, int from_start)
{
	size_t	i;
	t_room	*next_room_ptr;
	int		*target_depth;

	i = 0;
	next_room_ptr = NULL;
	while (i < room->links->size)
	{
		next_room_ptr = ft_vector_get(room->links, i);
		target_depth = from_start ? &next_room_ptr->start_len : &next_room_ptr->end_len;
		if (!room_is_start(next_room_ptr) && !room_is_end(next_room_ptr)
			&& (*target_depth > depth || *target_depth == -1))
		{
			*target_depth = depth;
			if (ft_vector_append(next_rooms, next_room_ptr) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	get_next_depth(size_t *depth, t_vect *rooms, t_vect *next, int from_start)
{
	size_t	i;
	t_room	*ptr;

	i = 0;
	while (i < rooms->size)
	{
		ptr = ft_vector_get(rooms, i);
		if (get_next_rooms(*depth, next, ptr, from_start) < 0)
			return (-1);
		i++;
	}
	(*depth)++;
	if (next->size > 0)
		return (1);
	else
		return (0);
}

int	weight_graph(t_room *target, int from_start)
{
	size_t	depth;
	int		status;
	t_vect	*next_rooms;
	t_vect	*rooms;

	depth = 1;
	status = 1;
	next_rooms = NULL;
	rooms = ft_vector_init(sizeof(t_room*), 0);
	if (!rooms || ft_vector_append(rooms, target) < 0)
		local_exit(rooms, next_rooms, -1);
	while (status > 0)
	{
		if (!(next_rooms = ft_vector_init(sizeof(t_room*), 0)))
			local_exit(rooms, next_rooms, -1);
		status = get_next_depth(&depth, rooms, next_rooms, from_start);
		ft_vector_free(rooms, &set_ptr_null);
		rooms = next_rooms;
		next_rooms = NULL;
	}
	return (local_exit(rooms, next_rooms, status));
}
