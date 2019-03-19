/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:00:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/19 20:39:19 by bopopovi         ###   ########.fr       */
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

static int	weight_room(t_room *target, int *target_depth, int current_depth)
{
	if (!room_is_start(target) && !room_is_end(target)
		&& (*target_depth > current_depth || *target_depth == -1))
	{
		*target_depth = current_depth;
		return (1);
	}
	return (0);
}

static int	*get_target_depth(t_room *target, t_room *src)
{
	int *target_depth;

	if (room_is_start(src))
		target_depth = &target->start_len;
	else
		target_depth = &target->end_len;
	return (target_depth);
}

static int	get_next_rooms(int dpt, t_vect *next_rms, t_room *rm, t_room *src)
{
	size_t	i;
	int		*target_depth;
	t_room	*next_room_ptr;

	i = 0;
	while (i < rm->links->size)
	{
		next_room_ptr = ft_vector_get(rm->links, i);
		target_depth = get_target_depth(next_room_ptr, src);
		if (weight_room(next_room_ptr, target_depth, dpt))
		{
			if (ft_vector_append(next_rms, next_room_ptr) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	get_next_depth(size_t *dpt, t_vect *rms, t_vect *next, t_room *src)
{
	size_t	i;
	t_room	*ptr;

	i = 0;
	while (i < rms->size)
	{
		ptr = ft_vector_get(rms, i);
		if (get_next_rooms(*dpt, next, ptr, src) < 0)
			return (-1);
		i++;
	}
	(*dpt)++;
	return (next->size > 0);
}

static t_vect	*add_first_room(t_room *src_room)
{
	t_vect *rooms;

	if (!(rooms = ft_vector_init(sizeof(t_room*), 0)))
		return (NULL);
	if (ft_vector_append(rooms, src_room) < 0)
	{
		local_exit(rooms, NULL, -1);
		return (NULL);
	}
	return (rooms);
}

int	weight_graph(t_room *src)
{
	size_t	depth;
	int		status;
	t_vect	*next_rooms;
	t_vect	*rooms;

	depth = 1;
	status = 1;
	if (!(rooms = add_first_room(src)))
		return (-1);
	while (status > 0)
	{
		if (!(next_rooms = ft_vector_init(sizeof(t_room*), 0)))
			return (local_exit(rooms, next_rooms, -1));
		status = get_next_depth(&depth, rooms, next_rooms, src);
		ft_vector_free(rooms, &set_ptr_null);
		rooms = next_rooms;
		next_rooms = NULL;
	}
	return (local_exit(rooms, next_rooms, status));
}
