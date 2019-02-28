/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:40:20 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/28 18:44:31 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_set		*init_new_set(int set_id)
{
	t_set *new_set;

	if (!(new_set = malloc(sizeof(*new_set))))
		return (NULL);
	new_set->nbr_of_paths = 0;
	new_set->biggest = 0;
	new_set->lowest = 0;
	new_set->diff = 0;
	new_set->id = set_id;
	new_set->paths = NULL;
	return (new_set);
}

int		set_add_path(t_set *set, t_path *path)
{
	if (ft_lstadd_data(&set->paths, &path, sizeof(path)) < 0)
		return (-1);
	set->nbr_of_paths += 1;
	return (0);
}

t_path	*set_get_path(t_set *set, int path_id)
{
	t_list *ptr;

	ptr = NULL;
	if (set)
	{
		ptr = set->paths;
		while (ptr)
		{
			if (path_get_id(*((t_path**)ptr->content)) == path_id)
				return (*((t_path**)ptr->content));
			ptr = ptr->next;
		}
	}
	return (NULL);
}

int		set_add_room_to_path(t_set *set, int path_id, t_room *room)
{
	t_path *path;

	path = NULL;
	if (set)
	{
		if (!(path = set_get_path(set, path_id)))
			return (-1);
		if (path_add_room(path, room) < 0)
			return (-1);
	}
	return (0);
}

void	set_free(t_set *set)
{
	set->nbr_of_paths = 0;
	set->biggest = 0;
	set->lowest = 0;
	set->diff = 0;
	if (set->paths)
	{
		ft_lstdel(&set->paths, (void*)&lst_free_path);
		set->paths = NULL;
	}
	free(set);
	set = NULL;
}
