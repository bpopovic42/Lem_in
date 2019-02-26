/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/26 19:51:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

/* UTILS **********************************************************************/

static void print_room_name(t_room **room)
{
	ft_putendl((*room)->name);
}

static void print_final_paths(t_set *final_paths)
{
	size_t i;
	t_list *path_ptr;
	t_dlist *ptr;

	i = 0;
	path_ptr = final_paths->paths;
	while (path_ptr != NULL)
	{
		ptr = ((*(t_path**)path_ptr->content)->head);
		ft_dlstiter_data(ptr, (void*)&print_room_name);
		path_ptr = path_ptr->next;
		ft_putendl("Next path :");
	}
}

/* BFS MAIN *******************************************************************/

static void mark_visited(t_list *paths)
{
	t_list		*ptr;
	t_dlist		*tmp;
	t_room		*room;

	ptr = paths;
	while (ptr)
	{
		tmp = *((t_dlist**)ptr->content);
		room = *((t_room**)tmp->content);
		if (!room->command || ft_strcmp("##end", room->command))
			room->visited = 1;
		ptr = ptr->next;
	}
}

static void record_final_path(t_dlist **base_path, t_room *room, t_set *final_paths)
{
	t_path *new_path;

	if (!(new_path = malloc(sizeof(*new_path))))
		exit(1);
	new_path->length = 0;
	new_path->head = ft_dlstdup(base_path);
	ft_dlstpush(&new_path->head, ft_dlstnew(&room, sizeof(room)));
	ft_lstpush(&final_paths->paths, ft_lstnew(&new_path, sizeof(new_path)));
	final_paths->nbr_of_paths += 1;
}

static void append_room_to_path(t_list **paths, t_dlist **base_path, t_room *room)
{
	t_dlist *new_path;

	new_path = NULL;
	new_path = ft_dlstdup(base_path);
	ft_dlstpush(&new_path, ft_dlstnew(&room, sizeof(room)));
	ft_lstadd(paths, ft_lstnew(&new_path, sizeof(new_path)));
}

static void get_next_rooms(t_list **paths, t_set *final_paths)
{
	t_list *path_ptr;
	t_room *last_room;
	t_room	*next;
	t_dlist *tmp;
	size_t i;

	path_ptr = *paths;
	last_room = NULL;
	next = NULL;
	while (path_ptr)
	{
		i = 0;
		tmp = *(t_dlist**)path_ptr->content;
		last_room = *((t_room**)tmp->content);
		while (i < last_room->links->size)
		{
			next = ft_vector_get(last_room->links, i);
			if (next->command && !ft_strcmp("##end", next->command))
			{
				record_final_path(path_ptr->content, next, final_paths);
			}
			else if (next->visited == 0)
			{
				append_room_to_path(paths, path_ptr->content, next);
			}
			i++;
		}
		path_ptr = path_ptr->next;
	}
}

static void	bfs(t_list *paths, t_set *final_paths)
{
	int depth;

	depth = 0;
	while (final_paths->nbr_of_paths < 3)
	{
		mark_visited(paths);
		get_next_rooms(&paths, final_paths);
		depth++;
	}
	print_final_paths(final_paths);
}

t_set		*init_set(t_set *path_set)
{
	if (!(path_set = malloc(sizeof(*path_set))))
		return (NULL);
	path_set->nbr_of_paths = 0;
	path_set->biggest = 0;
	path_set->lowest = 0;
	path_set->diff = 0;
	path_set->paths = NULL;
	return (path_set);
}

t_path	*new_path(t_path *path)
{
	if (!(path = malloc(sizeof(*path))))
		return (NULL);
	path->length = 0;
	path->head = NULL;
	return (path);
}

int		get_paths(t_graph *graph)
{
	t_list		*paths;
	t_set		*final_paths;
	t_dlist		*start;

	final_paths = NULL;
	start = NULL;
	paths = NULL;
	if (!(final_paths = init_set(final_paths)))
		return (1);
	start = ft_dlstnew(&graph->start, sizeof(graph->start));
	paths = ft_lstnew(&start, sizeof(start));
	bfs(paths, final_paths);
	return (0);
}
