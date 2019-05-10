/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:53:11 by bopopovi          #+#    #+#             */
/*   Updated: 2019/04/29 18:35:33 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_bfs_queue(t_queue **bfs, size_t nbr_of_rooms)
{
	if (!(*bfs = ft_memalloc(sizeof(**bfs))))
		return (-1);
	if (!((*bfs)->rooms = ft_memalloc(sizeof(t_room*) * nbr_of_rooms)))
		return (-1);
	(*bfs)->capacity = nbr_of_rooms;
	(*bfs)->size = 0;
	(*bfs)->head = 0;
	(*bfs)->tail = 0;
	return (0);
}

void	bfs_add(t_queue *bfs, t_room *room)
{
	if (bfs->tail + 1 >= (bfs->capacity - 1))
		bfs->tail = 0;
	else if (!(bfs->head == bfs->tail && bfs->size == 0))
		bfs->tail++;
	bfs->rooms[bfs->tail] = room;
	bfs->size++;
}

t_room	*bfs_pop(t_queue *bfs)
{
	t_room *tmp;

	tmp = bfs->rooms[bfs->head];
	bfs->rooms[bfs->head] = NULL;
	if (bfs->head + 1 >= (bfs->capacity - 1))
		bfs->head = 0;
	else
		bfs->head++;
	bfs->size--;
	return (tmp);
}
