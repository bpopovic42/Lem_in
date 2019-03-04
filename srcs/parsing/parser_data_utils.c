/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:40:03 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/04 11:55:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void	erase_ptr(void **ptr)
{
	ft_bzero(ptr, sizeof(ptr));
}

static void	del_id(int **id)
{
	**id = 0;
	free(*id);
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
		if (target->path_ids)
			ft_lstdel(&target->path_ids, (void*)&del_id);
		target->pos.x = 0;
		target->pos.y = 0;
		if (target->path_ids)
			ft_lstdel(&target->path_ids, &ft_bzero);
		free(room);
		room = NULL;
	}
}

void	init_graph(t_graph *graph)
{
	graph->nbr_of_rooms = 0;
	graph->nbr_of_links = 0;
	graph->start = NULL;
	graph->end = NULL;
	graph->room_list = ft_vector_init(sizeof(char*), 0);
	graph->rooms = ft_hash_newtable(100);
	graph->last_command = NULL;
}

void		free_graph(t_graph *graph)
{
	if (graph->room_list)
		ft_vector_free(graph->room_list, (void*)&ft_strdel);
	if (graph->rooms)
		ft_hash_freetable(&graph->rooms, &free_room);
	graph->nbr_of_rooms = 0;
	graph->nbr_of_links = 0;
	graph->room_list = NULL;
	graph->rooms = NULL;
	if (graph->last_command)
		ft_strdel(&graph->last_command);
}
