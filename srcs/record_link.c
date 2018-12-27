/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:06:50 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/27 16:22:08 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	record_link(t_graph *graph, char *room_a, char *room_b)
{
	t_room *ptr;

	ptr = ft_hashget_data(graph->rooms, room_a);
	if (!ptr->links)
		ptr->links = ft_vector_init(sizeof(room_a), 0);
	ft_vector_append(ptr->links, ft_strdup(room_b));
	graph->nbr_of_links++;
}
