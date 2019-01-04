/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:40:03 by bopopovi          #+#    #+#             */
/*   Updated: 2019/01/04 16:51:24 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void		free_room(void *room)
{
	t_room *target;

	target = room;
	if (target->command != NULL)
		ft_strdel(&(target->command));
	ft_strdel(&(target->name));
	if (target->links != NULL)
		ft_vector_free(target->links, (void*)(void**)&ft_strdel);
	target->pos.x = 0;
	target->pos.y = 0;
	free(room);
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
		ft_vector_free(graph->room_list, (void(*)(void**))&ft_strdel);
	if (graph->rooms)
		ft_hash_freetable(&graph->rooms, &free_room);
	graph->nbr_of_rooms = 0;
	graph->nbr_of_links = 0;
	graph->room_list = NULL;
	graph->rooms = NULL;
	if (graph->last_command)
		ft_strdel(&graph->last_command);
}

static const char			*get_error_msg(int error_code)
{
	if (error_code == EINVANT)
		return (EINVANT_MSG);
	else if (error_code == ENEROOM)
		return (ENEROOM_MSG);
	else if (error_code == ENELINK)
		return (ENELINK_MSG);
	else if (error_code == EINVMAP)
		return (EINVMAP_MSG);
	else
		return ("Undefined error.");
}

void			lemin_perror(int error_code, char *file)
{
	if (ERR_DBG)
		ft_printf("{red}");
	ft_putstr("ERROR");
	if (ERR_DBG)
	{
		ft_printf(": %s\n", get_error_msg(error_code));
		ft_printf("{red}Problematic line :\n%.*s {red}<---{eoc}\n", ft_strlen(file) - 1, file);
	}
}
