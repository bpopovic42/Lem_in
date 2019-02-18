/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:12:38 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/18 21:02:32 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		is_end_room(t_graph *graph, char *room)
{
	if (!ft_strcmp(graph->end->name, room))
		return (1);
	else
		return (0);
}

int		found_end(t_graph *graph, t_vect *room_list)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	if (room_list)
	{
		while ((size_t)i < room_list->size)
		{
			tmp = ft_vector_get(room_list, i);
			if (is_end_room(graph, tmp))
				return (1);
			i++;
		}
	}
	return (0);
}

int		is_visited(t_room *room)
{
	return (room->visited);
}

int		is_blocked(t_graph *graph, t_vect *room_list)
{
	int i;
	int j;
	char *name_tmp;
	t_room *room_tmp;

	i = 0;
	j = 0;
	name_tmp = NULL;
	room_tmp = NULL;
	if (room_list)
	{
		while ((size_t)i < room_list->size)
		{
			name_tmp = ft_vector_get(room_list, i);
			room_tmp = ft_hashget_data(graph->rooms, name_tmp);
			while ((size_t)j < room_tmp->links->size)
			{
				if (!is_visited(ft_hashget_data(graph->rooms, ft_vector_get(room_tmp->links, j))))
					return (0);
				j++;
			}
			i++;
		}
	}
	return (1);
}

static void		path_record(t_vect *paths, t_dlist *current, char *new_room)
{
	t_dlist *new_path;

	new_path = ft_dlstdup(&current);
	ft_dlstpush(&new_path, ft_dlstnew(new_room, sizeof(char*)));
	ft_vector_append(paths, new_path);
}

static t_dlist	*get_current_path(t_vect *paths, char *room)
{
	size_t i;
	t_dlist *tmp;

	i = 0;
	tmp = NULL;
	while (i < paths->size)
	{
		tmp = ft_vector_get(paths, i);
		if (!ft_strcmp(tmp->content, room))
			return (tmp);
		i++;
	}
	return (NULL);
}

static void		get_links_for_room(t_htable *rooms, t_vect **new_list, t_room *target, t_vect *paths)
{
	int		i;
	char *tmp;
	t_dlist *current_path;

	i = 0;
	tmp = NULL;
	current_path = get_current_path(paths, target->name);
	if (target->links)
	{
		while ((size_t)i < target->links->size)
		{
			tmp = ft_strdup(ft_vector_get(target->links, i));
			if (!is_visited(ft_hashget_data(rooms, tmp)))
			{
				path_record(paths, current_path, tmp);
				ft_vector_append(*new_list, tmp);
			}
			i++;
		}
	}
	//if (current_path)
	//	ft_dlstdel(&current_path, (void*)&ft_strdel);
}

static void		get_next_list(t_htable *rooms, t_vect **room_list, t_vect *paths)
{
	t_vect *new_list;
	t_room *room_ptr;
	int i;

	new_list = ft_vector_init(sizeof(char*), 0);
	i = 0;
	while ((size_t)i < (*room_list)->size)
	{
		room_ptr = ft_hashget_data(rooms, ft_vector_get((*room_list), i));
		get_links_for_room(rooms, &new_list, room_ptr, paths);
		i++;
	}
	ft_vector_free(*room_list, (void*)(void**)&ft_strdel);
	*room_list = new_list;
}

static void mark_visited(t_graph *graph, t_vect *room_list)
{
	t_room *tmp;
	int i;

	tmp = NULL;
	i = 0;
	while ((size_t)i < room_list->size)
	{
		tmp = ft_hashget_data(graph->rooms, ft_vector_get(room_list, i));
		tmp->visited = 1;
		i++;
	}
}

/*static void print_room_name(char *name)
{
	ft_putstr(name);
	ft_putchar(' ');
}*/

static void print_good_path(t_vect *paths, char *end)
{
	size_t i;
	t_dlist *tmp;
	i = 0;
	tmp = NULL;
	while (i < paths->size)
	{
		tmp = ft_vector_get(paths, i);
		if (!ft_strcmp(tmp->content, end))
		{
			while (tmp != NULL)
			{
				ft_putendl(tmp->content);
				tmp = tmp->next;
			}
			break;
		}
		i++;
	}
}

static void	bfs_test(t_graph *graph, t_vect *paths, t_vect *room_list, int depth)
{
	mark_visited(graph, room_list);
	get_next_list(graph->rooms, &room_list, paths);
	if (found_end(graph, room_list))
	{
		ft_printf("Shortest path depth : %d\n", depth);
		//ft_vector_iter(room_list, (void*)(void*)&print_room_name);
		//ft_putchar('\n');
		print_good_path(paths, graph->end->name);
	}
	else if (is_blocked(graph, room_list))
		ft_printf("No path to end.\n");
	else
		bfs_test(graph, paths, room_list, depth + 1);
}

int		get_paths(t_graph *graph)
{
	t_vect *room_list;
	t_vect *paths;
	t_dlist *start;

	room_list = ft_vector_init(sizeof(char*), 0);
	paths = ft_vector_init(sizeof(t_dlist*), 0);
	start = ft_dlstnew(graph->start->name, sizeof(char*));
	ft_vector_append(paths, start);
	ft_vector_append(room_list, ft_strdup(graph->start->name));
	bfs_test(graph, paths, room_list, 0);
	return (0);
}
