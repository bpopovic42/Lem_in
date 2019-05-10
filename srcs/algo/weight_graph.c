/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_graph.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 10:49:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/09 20:38:14 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int			clean_weight(t_queue *bfs, t_room *src, t_room *target)
{
	t_room	*current;
	t_room	*next_ptr;
	t_node	*links_ptr;

	bfs_add(bfs, src);
	//ft_printf("CLEAN WEIGHT START\n");
	while (bfs->size > 0)
	{
		current = bfs_pop(bfs);
		links_ptr = current->links->head;
		while (links_ptr)
		{
			next_ptr = *(t_room**)links_ptr->data;
			//ft_printf("%s %d\n", next_ptr->name, next_ptr->cleaned);
			if (next_ptr != src && next_ptr != target && next_ptr->end_distance >= 0)
			{
				//ft_printf("cleaning %s\n", next_ptr->name);
				next_ptr->end_distance = -1;
				bfs_add(bfs, next_ptr);
			}
			links_ptr = links_ptr->next;
		}
	}
	//ft_printf("CLEAN WEIGHT END\n\n");
	return (0);
}

int		weight_graph(t_queue *bfs, t_room *src, t_room *target)
{
	t_room	*current;
	t_room	*next_ptr;
	t_node	*links_ptr;

	bfs_add(bfs, src);
	src->end_distance = 0;
	//ft_printf("WEIGHT START\n");
	while (bfs->size > 0)
	{
		current = bfs_pop(bfs);
		links_ptr = current->links->head;
		while (links_ptr)
		{
			next_ptr = *(t_room**)links_ptr->data;
			if ((next_ptr != src && next_ptr != target && next_ptr->end_distance < 0)
				|| (next_ptr->end_distance >= 0 && next_ptr->end_distance > current->end_distance + 1))
			{
				if (!next_ptr->blocked)
				{
					//ft_printf("weighting %s\n", next_ptr->name);
					next_ptr->cleaned = 0;
					next_ptr->end_distance = current->end_distance + 1;
					bfs_add(bfs, next_ptr);
				}
			}
			links_ptr = links_ptr->next;
		}
	}
	//ft_printf("WEIGHT END\n");
	return (0);
}
