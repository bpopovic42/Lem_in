/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:00:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/19 21:07:11 by bopopovi         ###   ########.fr       */
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

static int	get_next_layer_for_room(t_room *room, int depth, t_vect *next_layer, t_room *src)
{
	size_t	i;
	int		*target_depth;
	t_room	*next_room_ptr;

	i = 0;
	while (i < room->links->size)
	{
		next_room_ptr = ft_vector_get(room->links, i);
		target_depth = get_target_depth(next_room_ptr, src);
		if (weight_room(next_room_ptr, target_depth, depth))
		{
			if (ft_vector_append(next_layer, next_room_ptr) < 0)
				return (-1);
		}
		i++;
	}
	return (0);
}

static int	get_next_layer(size_t *depth, t_vect *curr_layer, t_vect **next_layer, t_room *src)
{
	size_t	i;
	t_room	*room_ptr;

	i = 0;
	if (!(*next_layer = ft_vector_init(sizeof(t_room*), 0)))
		return (-1);
	while (i < curr_layer->size)
	{
		room_ptr = ft_vector_get(curr_layer, i);
		if (get_next_layer_for_room(room_ptr, *depth, *next_layer, src) < 0)
			return (-1);
		i++;
	}
	(*depth)++;
	return ((*next_layer)->size > 0);
}

static t_vect	*get_initial_layer(t_room *initial_room)
{
	t_vect *initial_layer;

	if (!(initial_layer = ft_vector_init(sizeof(t_room*), 0)))
		return (NULL);
	if (ft_vector_append(initial_layer, initial_room) < 0)
	{
		local_exit(initial_layer, NULL, -1);
		return (NULL);
	}
	return (initial_layer);
}

static void		swap_layers(t_vect **current_layer, t_vect **next_layer)
{
	ft_vector_free(*current_layer, &set_ptr_null);
	*current_layer = *next_layer;
	*next_layer = NULL;
}

int	weight_graph(t_room *src)
{
	size_t	depth;
	int		status;
	t_vect	*next_layer;
	t_vect	*curr_layer;

	depth = 1;
	next_layer = NULL;
	if (!(curr_layer = get_initial_layer(src)))
		return (-1);
	while ((status = get_next_layer(&depth, curr_layer, &next_layer, src)) > 0)
		swap_layers(&curr_layer, &next_layer);
	return (local_exit(curr_layer, next_layer, status));
}
