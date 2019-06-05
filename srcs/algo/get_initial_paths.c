/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_initial_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:24:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 18:45:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	path_free(t_path **path)
{
	ft_bzero(*path, sizeof(**path));
	free(*path);
	(*path) = NULL;
}

t_path	*path_new(t_room *head, int path_length)
{
	t_path *new_path;

	if (!(new_path = ft_memalloc(sizeof(*new_path))))
		return (NULL);
	new_path->head = head;
	new_path->length = path_length;
	new_path->final_length = -1;
	return (new_path);
}

static void	mark_rooms_distance_from_end(t_queue *bfs, t_room *end)
{
	t_room	*current;
	t_room	*next_ptr;
	t_node	*links_ptr;

	bfs_add(bfs, end);
	end->end_distance = 0;
	while (bfs->size > 0)
	{
		current = bfs_pop(bfs);
		links_ptr = current->links->head;
		while (links_ptr)
		{
			next_ptr = *(t_room**)links_ptr->data;
			if (!room_is_end(next_ptr) && !room_is_start(next_ptr) && next_ptr->end_distance < 0)
			{
				next_ptr->end_distance = current->end_distance + 1;
				bfs_add(bfs, next_ptr);
			}
			links_ptr = links_ptr->next;
		}
	}
}

static int	get_valid_paths(t_room *start, t_list *paths)
{
	t_node	*links_ptr;
	t_room	*room_ptr;
	t_path	*tmp;

	links_ptr = start->links->head;
	while (links_ptr)
	{
		room_ptr = *(t_room**)links_ptr->data;
		if (room_ptr->end_distance >= 0)
		{
			if (!(tmp = path_new(room_ptr, room_ptr->end_distance)))
				return (-1);
			if (ft_lstadd_data(paths, &tmp, sizeof(tmp)) < 0)
				return (-1);
		}
		links_ptr = links_ptr->next;
	}
	return (paths->size > 0 ? 1 : 0);
}

int		get_initial_paths(t_graph *graph, t_queue *bfs, t_list *paths)
{
	ft_bzero(paths, sizeof(*paths));
	mark_rooms_distance_from_end(bfs, graph->end);
	return (get_valid_paths(graph->start, paths));
}
