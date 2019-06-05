/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 01:29:10 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 16:46:54 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	print_ant(int ant, char *room_name, int *first_ant)
{
	if (!*first_ant)
		ft_printf(" L%d-%s", ant, room_name);
	else
	{
		*first_ant = 0;
		ft_printf("L%d-%s", ant, room_name);
	}
}

void	move_ant_to_next_room(t_room *room, int *first_ant)
{
	if (room->ant)
	{
		print_ant(room->ant, room->solution_to->name, first_ant);
		if (room_is_end(room->solution_to))
			room->solution_to->ant++;
		else
			room->solution_to->ant = room->ant;
		if (!room_is_end(room))
			room->ant = 0;
	}
}

void	move_new_ant_to_path(t_path *path, int *ants_count, int *first_ant)
{
	t_room *ptr;

	ptr = path->head;
	if (path->ants > 0)
	{
		if (room_is_end(ptr))
			ptr->ant++;
		else
			ptr->ant = (*ants_count)++;
		path->ants--;
		print_ant(ptr->ant, ptr->name, first_ant);
	}
}

void	advance_path_ants(t_path *path, int *ants_count, int *first_ant)
{
	t_room *room_ptr;

	room_ptr = path->last_ant;
	if (room_ptr == path->head && room_ptr->ant > 0)
	{
		if (room_is_end(room_ptr->solution_to) || !room_ptr->solution_to->ant)
			move_ant_to_next_room(room_ptr, first_ant);
	}
	while (room_ptr && !room_is_start(room_ptr))
	{
		if (!room_ptr->ant && room_ptr != path->head)
			break;
		if (room_ptr != path->head)
			move_ant_to_next_room(room_ptr, first_ant);
		else
		{
			if (room_ptr->ant > 0)
				move_ant_to_next_room(room_ptr, first_ant);
			move_new_ant_to_path(path, ants_count, first_ant);
		}
		room_ptr = room_ptr->solution_from;
	}
	if (!room_is_end(path->last_ant->solution_to)
		&& path->last_ant->solution_to->ant > 0)
		path->last_ant = path->last_ant->solution_to;
}

void	move_ants(t_path *path, int *ants_count, int *first_ant)
{
	if (!room_is_end(path->head))
	{
		if (!path->last_ant)
			path->last_ant = path->head;
		advance_path_ants(path, ants_count, first_ant);
	}
	else
	{
		move_new_ant_to_path(path, ants_count, first_ant);
		return;
	}
}
