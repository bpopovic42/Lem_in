/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:41 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/29 19:33:21 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	erase_ptr(void *ptr)
{
	ft_bzero(&ptr, sizeof(ptr));
}

int			init_graph(t_graph *graph)
{
	ft_bzero(graph, sizeof(*graph));
	if (!(graph->room_list = ft_vector_init(sizeof(t_room*), 0)))
		return (-1);
	if (!(graph->rooms = ft_hash_newtable(10000)))
		return (-1);
	return (0);
}

void		free_graph(t_graph *graph)
{
	if (graph->room_list)
		ft_vector_free(graph->room_list, (void*)&free_room);
	if (graph->rooms)
		ft_hash_freetable(&graph->rooms, (void*)&erase_ptr);
	if (graph->last_command)
		ft_strdel(&graph->last_command);
	ft_bzero(graph, sizeof(*graph));
}
