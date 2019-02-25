/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/25 20:28:43 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

/* UTILS **********************************************************************/

static void print_room_name(t_room **room)
{
	ft_putendl((*room)->name);
}

static void print_final_paths(t_graph *graph)
{
	size_t i;
	t_dlist *ptr;

	i = 0;
	while (i < graph->paths->size)
	{
		ptr = ft_vector_get(graph->paths, i);
		ft_dlstiter_data(ptr, (void*)&print_room_name);
		i++;
	}
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
		room = *((t_room**)(*(t_dlist**)ptr->content)->content);// Here we get ptr->content which is a t_dlist* pointer saved in a void* pointer, therefore a t_dlist** pointer, same applies for ptr->content->content
		if (ft_strcmp(graph->end->name, room->name))
			room->visited = 1;
		ptr = ptr->next;
	}
}

static void record_final_path(t_graph *graph, t_dlist **base_path, t_room *room)
{
	t_dlist *final_path;

	final_path = ft_dlstdup(base_path);
	ft_dlstpush(&final_path, ft_dlstnew(&room, sizeof(room)));
	ft_vector_append(graph->paths, final_path);
}

static void append_room_to_path(t_list **paths, t_dlist **base_path, t_room *room)
{
	t_dlist *new_path;

	new_path = ft_dlstdup(base_path);
	ft_dlstpush(&new_path, ft_dlstnew(&room, sizeof(room)));
	ft_lstadd(paths, ft_lstnew(&new_path, sizeof(t_dlist**)));
}

static void get_next_rooms(t_graph *graph, t_list **paths)
{
	t_list *path_ptr;
	t_room *last_room;
	t_room	*next;
	size_t i;

	path_ptr = *paths;
	last_room = NULL;
	next = NULL;
	while (path_ptr)
	{
		i = 0;
		last_room = *((t_room**)(*(t_dlist**)path_ptr->content)->content);
		while (i < last_room->links->size)
		{
			next = get_room_from_vector(graph, last_room->links, i);
			if (next->command && !ft_strcmp("##end", next->command))
			{
				ft_putendl("Found end !!!!!!!!!!!!");
				record_final_path(graph, path_ptr->content, next);
			}
			else if (next->visited == 0)
				append_room_to_path(paths, path_ptr->content, next);
			i++;
		}
		path_ptr = path_ptr->next;
	}
}

static void	bfs(t_graph *graph, t_list *paths, int depth)
{
	while (graph->paths->size == 0)
	{
		mark_visited(graph, paths);
		get_next_rooms(graph, &paths);
		depth++;
	}
	print_final_paths(graph);
}

int		get_paths(t_graph *graph)
{
	t_list *paths;
	t_dlist *start;

	paths = NULL;
	start = NULL;
	start = ft_dlstnew(&graph->start, sizeof(graph->start)); // content (&graph->start) will be dereferenced and copied, therefore the pointer 'graph->start' will be stored in new->content
	paths = ft_lstnew(&start, sizeof(start)); // Same here
	bfs(graph, paths, 0);
	return (0);
}
