/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:09:29 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/21 20:41:53 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	erase_ptr(void **ptr)
{
	ft_bzero(ptr, sizeof(ptr));
}

int			room_is_end(t_room *room)
{
	if (room->command && !ft_strcmp("##end", room->command))
		return (1);
	return (0);
}

int			room_is_start(t_room *room)
{
	if (room->command && !ft_strcmp("##start", room->command))
		return (1);
	return (0);
}

t_room		*new_room(char *name, char **cmd, t_pos *coord)
{
	t_room	*new_room;

	if (!(new_room = malloc(sizeof(*new_room))))
		return (NULL);
	new_room->command = *cmd;
	*cmd = NULL;
	if (!(new_room->name = ft_strdup(name)))
		return (NULL);
	new_room->pos = *coord;
	new_room->depth = -1;
	new_room->start_len = -1;
	new_room->start_id = -1;
	new_room->end_len = -1;
	new_room->end_id = -1;
	if (!(new_room->links = ft_vector_init(sizeof(t_room*), 0)))
		return (NULL);
	return (new_room);
}

void		free_room(void *room)
{
	t_room *target;

	target = room;
	if (room)
	{
		if (target->command != NULL)
			ft_strdel(&(target->command));
		ft_strdel(&(target->name));
		if (target->links != NULL)
			ft_vector_free(target->links, (void*)&erase_ptr);
		target->pos.x = 0;
		target->pos.y = 0;
		target->depth = 0;
		free(room);
		room = NULL;
	}
}
