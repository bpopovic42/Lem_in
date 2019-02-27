/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:00:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/02/27 17:14:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*init_new_path(t_dlist *path, size_t path_length)
{
	t_path *new_path;

	if (!(new_path = malloc(sizeof(*new_path))))
		return (NULL);
	new_path->length = path_length;
	new_path->head = path;
	return (new_path);
}

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

int		add_new_path(t_set *path_set, t_dlist *path, size_t path_length)
{
	t_path		*new_path;

	if (!(new_path = init_new_path(path, path_length)))
		return (-1);
	if (ft_lstadd_data(&path_set->paths, &new_path, sizeof(new_path)) < 0)
		return (-1);
	return (0);
}
