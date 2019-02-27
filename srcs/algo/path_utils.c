/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:00:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/27 19:25:13 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*init_new_path(void)
{
	t_path *new_path;

	if (!(new_path = malloc(sizeof(*new_path))))
		return (NULL);
	new_path->id = 0;
	new_path->length = 0;
	new_path->conflicts = NULL;
	new_path->head = NULL;
	return (new_path);
}

void	path_set_id(t_path *path, int id)
{
	if (path)
		path->id = id;
}

void	path_set_path(t_path *path, t_dlist *head, size_t length)
{
	if (path)
	{
		path->head = head;
		path->length = length;
	}
}

int		path_add_room(t_path *path, t_room *room)
{
	t_dlist *new_room;

	new_room = NULL;
	if (path)
	{
		if (!(new_room = ft_dlstnew(&room, sizeof(room))))
			return (-1);
		ft_dlstadd(&path->head, new_room);
		return (0);
	}
	return (-1);
}

void	path_set_conflicts(t_path *path, t_list *conflicts)
{
	if (path)
		path->conflicts = conflicts;
}

int		path_add_conflict(t_path *path, int conflict_id)
{
	t_list *new_conflict;

	new_conflict = NULL;
	if (path)
	{
		if (!(new_conflict = ft_lstnew(&conflict_id, sizeof(conflict_id))))
			return (-1);
		ft_lstadd(&path->conflicts, new_conflict);
		return (0);
	}
	return (-1);
}

t_path *path_duplicate(t_path *origin)
{
	t_path		*new_path;
	t_dlist		*path_dup;
	t_list		*conflicts_dup;

	if (!(new_path = init_new_path()))
		return (NULL);
	if (!(path_dup = ft_dlstdup(&origin->head)))
		return (NULL);
	if (!(conflicts_dup = ft_lstdup(&origin->conflicts)))
		return (NULL);
	path_set_id(new_path, origin->id);
	path_set_path(new_path, path_dup, origin->length);
	path_set_conflicts(new_path, conflicts_dup);
	return (new_path);
}

static void		free_ptr(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	path_free_path(t_path *path)
{
	ft_dlstdel(&path->head, (void*)&free_ptr);
	path->head = NULL;
	path->length = 0;
}

void	path_free_conflicts(t_path *path)
{
	ft_lstdel(&path->conflicts, (void*)&free_ptr);
	path->conflicts = NULL;
}

void	path_free(t_path *path)
{
	path->id = 0;
	path_free_path(path);
	path_free_conflicts(path);
	free(path);
	path = NULL;
}

/*
** Dereference from list's generic void pointer field
*/

void	lst_free_path(t_path ***path)
{
	path_free(**path);
	free(*path);
	*path = NULL;
}
