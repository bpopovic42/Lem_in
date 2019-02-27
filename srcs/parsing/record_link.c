/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:06:50 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/26 15:28:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	record_link(t_graph *graph, char *room_a, char *room_b)
{
	t_room *ptr_a;
	t_room *ptr_b;

	ptr_a = ft_hashget_data(graph->rooms, room_a);
	ptr_b = ft_hashget_data(graph->rooms, room_b);
	if (!ptr_a->links)
		ptr_a->links = ft_vector_init(sizeof(ptr_b), 0);
	if (!ptr_b->links)
		ptr_b->links = ft_vector_init(sizeof(ptr_a), 0);
	ft_vector_append(ptr_a->links, ptr_b);
	ft_vector_append(ptr_b->links, ptr_a);
	graph->nbr_of_links++;
}
