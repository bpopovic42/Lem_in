/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:40:20 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/27 19:10:31 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_set		*init_new_set(void)
{
	t_set *new_set;

	if (!(new_set = malloc(sizeof(*new_set))))
		return (NULL);
	new_set->nbr_of_paths = 0;
	new_set->biggest = 0;
	new_set->lowest = 0;
	new_set->diff = 0;
	new_set->paths = NULL;
	return (new_set);
}

int		set_add_new_path(t_set *path_set, t_dlist *path, size_t path_length)
{
	t_path		*new_path;

	if (!(new_path = init_new_path()))
		return (-1);
	path_set_path(new_path, path, path_length);
	if (ft_lstadd_data(&path_set->paths, &new_path, sizeof(new_path)) < 0)
		return (-1);
	return (0);
}

void	set_free(t_set *set)
{
	set->nbr_of_paths = 0;
	set->biggest = 0;
	set->lowest = 0;
	set->diff = 0;
	ft_lstdel(&set->paths, (void*)&lst_free_path);
	set->paths = NULL;
	free(set);
	set = NULL;
}
