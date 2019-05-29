/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:59:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/29 21:09:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		link_add(t_graph *graph, t_room *a, t_room *b)
{
	if (ft_lstadd_data(a->links, &b, sizeof(b)) < 0)
		return (-1);
	if (ft_lstadd_data(b->links, &a, sizeof(a)) < 0)
		return (-1);
	graph->nbr_of_links++;
	return (0);
}

int		room_has_link(t_room *room_a, t_room *room_b)
{
	t_node	*node_ptr;
	t_room	*link;

	node_ptr = room_a->links->head;
	while (node_ptr)
	{
		link = *(t_room**)node_ptr->data;
		if (!ft_strcmp(link->name, room_b->name))
			return (1);
		node_ptr = node_ptr->next;
	}
	return (0);
}
