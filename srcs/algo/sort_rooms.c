/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:11:36 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/20 17:03:13 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		sort_by_end_distance(void *node_a, void *node_b)
{
	t_room *room_a;
	t_room *room_b;

	room_a = *(t_room**)node_a;
	room_b = *(t_room**)node_b;
	return (room_a->end_distance < room_b->end_distance);
}

void	assign_paths_ids(t_list *start_rooms)
{
	int		i;
	t_node	*room_ptr;

	i = 0;
	room_ptr = start_rooms->head;
	while (room_ptr)
	{
		(*(t_room**)room_ptr->data)->pid = i;
		room_ptr = room_ptr->next;
		i++;
	}
}

t_list	*get_sorted_start_rooms(t_room *start)
{
	t_room	*ptr;
	t_node	*links_ptr;
	t_list	*start_rooms;

	ptr = NULL;
	if (!(start_rooms = ft_lstnew()))
		return (NULL);
	if (start && start->links)
	{
		links_ptr = start->links->head;
		while (links_ptr)
		{
			ptr = *(t_room**)links_ptr->data;
			if (ptr && ptr->end_distance >= 0)
			{
				if (ft_lstadd_data(start_rooms, &ptr, sizeof(ptr)) < 0)
					return (NULL);
			}
			links_ptr = links_ptr->next;
		}
	}
	ft_lstsort(start_rooms, &sort_by_end_distance);
	assign_paths_ids(start_rooms);
	return (start_rooms);
}
