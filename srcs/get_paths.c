/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/19 20:59:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

/* UTILS **********************************************************************/

static void print_final_paths(t_graph *graph)
{
	size_t i;
	t_dlist *ptr;

	i = 0;
	while (i < graph->paths->size)
	{
		ptr = ft_vector_get(graph->paths, i);
		ft_dlstiter_data(ptr, (void*)&ft_putendl);
		i++;
	}
}

static t_room	*get_last_room_in_path(t_graph *graph, t_dlist *path)
{
	char *room_name;

	room_name = path->content;
	return (ft_hashget_data(graph->rooms, room_name));
}

static t_room *get_room_from_vector(t_graph *graph, t_vect *v, size_t index)
{
	t_room	*room;
	char	*room_name;

	room_name = ft_vector_get(v, index);
	room = ft_hashget_data(graph->rooms, room_name);
	return (room);
}


/* BFS MAIN *******************************************************************/

static void mark_visited(t_graph *graph, t_list *paths)
{
	t_list		*ptr;
	t_room		*room;

	ptr = paths;
	while (ptr)
	{
		room = get_last_room_in_path(graph, *((t_dlist**)ptr->content));
		if (ft_strcmp(graph->end->name, room->name))
			room->visited = 1;
		ptr = ptr->next;
	}
}

static void record_final_path(t_graph *graph, t_dlist *base_path, char *room)
{
	t_dlist *final_path;

	final_path = ft_dlstdup(&base_path);
	ft_dlstpush(&final_path, ft_dlstnew(room, sizeof(char*)));
	ft_vector_append(graph->paths, &final_path);
}

static void append_room_to_path(t_list *paths, t_dlist *base_path, char *room)
{
	t_dlist *new_path;

	new_path = ft_dlstdup(&base_path);
	ft_dlstpush(&new_path, ft_dlstnew(room, sizeof(char*)));
	ft_lstadd(&paths, ft_lstnew(&new_path, sizeof(t_dlist**)));
}

static void get_next_rooms(t_graph *graph, t_list *paths)
{
	t_list *path_ptr;
	t_room *last_room;
	size_t i;

	path_ptr = paths;
	last_room = NULL;
	while (path_ptr)
	{
		i = 0;
		last_room = get_last_room_in_path(graph, path_ptr->content);
		//add_next_rooms_to_path(paths, path_ptr, last_room);
		while (i < last_room->links->size)
		{
			if (is_end(last_room->links, i))
				record_final_path(graph, path_ptr->content, last_room->name);
			else if (last_room->visited == 0)
				append_room_to_path(paths, path_ptr->content, last_room->name);
			i++;
		}
		path_ptr = paths->next;
	}
}

static void	bfs_test(t_graph *graph, t_list *paths, int depth)
{
	mark_visited(graph, paths);
	get_next_rooms(graph, paths);
	if (graph->paths->size > 0)
		print_final_paths(graph);
	//else if (is_blocked(graph, paths))
	//	ft_printf("No path to end.\n");
	else
		bfs_test(graph, paths, depth + 1);
}

int		get_paths(t_graph *graph)
{
	t_list *paths;
	t_dlist *start;

	start = ft_dlstnew(graph->start->name, sizeof(char*));
	ft_lstadd(&paths, ft_lstnew(&start, sizeof(t_dlist**)));
	bfs_test(graph, paths, 0);
	return (0);
}
