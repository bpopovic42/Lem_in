/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:49:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 18:30:47 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	clean_graph(t_graph *graph)
{
	size_t i;
	t_room *room;

	i = 0;
	while (i < graph->room_list->size)
	{
		room = ft_vector_get(graph->room_list, i);
		if (!room_is_start(room) && !room->cleaned)
		{
			room->start_distance = -1;
			room->end_distance = -1;
			room->final_distance = -1;
			room->blocked = 0;
			room->cleaned = 1;
			room->from = NULL;
			room->to = NULL;
		}
		i++;
	}
}
