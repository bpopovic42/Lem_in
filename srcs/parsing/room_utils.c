/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:09:29 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/24 20:48:54 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	erase_ptr(void **ptr)
{
	free(*ptr);
	ft_bzero(ptr, sizeof(ptr));
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
	new_room->end_distance = -1;
	new_room->start_distance = -1;
	new_room->final_distance = -1;
	new_room->pid = -1;
	new_room->from = NULL;
	new_room->to = NULL;
	new_room->blocked = 0;
	new_room->cleaned = 1;
	new_room->recorded = 0;
	new_room->solution_to = NULL;
	new_room->solution_from = NULL;
	new_room->solution_len = -1;
	new_room->is_solution = 0;
	new_room->ant = 0;
	if (!(new_room->links = ft_lstnew()))
		return (NULL);
	return (new_room);
}

void		free_room(void *room)
{
	t_room *target;

	target = *(t_room**)room;
	if (target)
	{
		if (target->command != NULL)
			ft_strdel(&(target->command));
		ft_strdel(&(target->name));
		if (target->links != NULL)
			ft_lstdel(target->links, (void*)&erase_ptr);
		target->pos.x = 0;
		target->pos.y = 0;
		free(target);
		target = NULL;
	}
}

void	free_room_ptr(void *data, size_t data_size)
{
	t_room **ptr;

	ptr = *(t_room***)data;
	ft_bzero(ptr, data_size);
	free(ptr);
}
