/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:09:29 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 17:58:15 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	erase_ptr(void **ptr)
{
	free(*ptr);
	ft_bzero(ptr, sizeof(ptr));
}

void		free_room_ptr(void *data, size_t data_size)
{
	t_room **ptr;

	ptr = *(t_room***)data;
	ft_bzero(ptr, data_size);
	free(ptr);
}

void		free_room(t_room **room)
{
	t_room *target;

	target = *(t_room**)room;
	if (target)
	{
		if (target->command != NULL)
			ft_strdel(&(target->command));
		if (target->links != NULL)
			ft_lstdel(target->links, (void*)&erase_ptr);
		ft_strdel(&(target->name));
		ft_bzero(&target->pos, sizeof(target->pos));
		ft_memdel((void**)&target);
	}
}

static void	initialize_room_data(t_room *room, t_pos *coord)
{
	room->pos = *coord;
	room->end_distance = -1;
	room->start_distance = -1;
	room->final_distance = -1;
	room->from = NULL;
	room->to = NULL;
	room->blocked = 0;
	room->cleaned = 1;
	room->recorded = 0;
	room->solution_to = NULL;
	room->solution_from = NULL;
	room->solution_len = -1;
	room->is_solution = 0;
	room->ant = 0;
}

t_room		*new_room(char *name, t_pos *coord)
{
	t_room	*new_room;

	if (!(new_room = ft_memalloc(sizeof(*new_room))))
		return (NULL);
	if (!(new_room->name = ft_strdup(name)))
	{
		free_room(&new_room);
		return (NULL);
	}
	if (!(new_room->links = ft_lstnew()))
	{
		free_room(&new_room);
		return (NULL);
	}
	initialize_room_data(new_room, coord);
	return (new_room);
}
