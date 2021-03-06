/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:12:42 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 19:14:05 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_path(t_path **path)
{
	ft_bzero(*path, sizeof(*path));
	ft_memdel((void**)path);
}

void	free_path_from_node(t_path ***path)
{
	free_path(*path);
	ft_memdel((void**)path);
}

t_path	*path_new(void)
{
	t_path *new_path;

	if (!(new_path = ft_memalloc(sizeof(*new_path))))
		return (NULL);
	new_path->final_length = -1;
	new_path->length = -1;
	return (new_path);
}
