/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:40:03 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/27 13:23:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_room(void *room)
{
	if (((t_room*)room)->command != NULL)
		ft_strdel(&(((t_room*)room)->command));
	ft_strdel(&(((t_room*)room)->name));
	if (((t_room*)room)->links)
		ft_vector_free(((t_room*)room)->links, (void*)(void**)&ft_strdel);
	((t_room*)room)->pos.x = 0;
	((t_room*)room)->pos.y = 0;
	free(room);
}

void	init_graph(t_graph *graph)
{
	graph->size = 0;
	graph->start = NULL;
	graph->end = NULL;
	graph->room_list = ft_vector_init(sizeof(char*), 0);
	graph->rooms = ft_hash_newtable(100);
}
