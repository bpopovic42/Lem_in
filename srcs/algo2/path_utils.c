/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:12:42 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/13 15:30:03 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_path(t_path ***path)
{
	ft_bzero(**path, sizeof(***path));
	ft_memdel((void**)*path);
}

t_path	*path_new()
{
	t_path *new_path;

	if (!(new_path = ft_memalloc(sizeof(*new_path))))
		return (NULL);
	new_path->final_length = -1;
	new_path->length = -1;
	return (new_path);
}

void	path_set_head(t_path *path, t_room *head)
{
	path->head = head;
}

void	path_set_final_length(t_path *path, int final_length)
{
	path->final_length = final_length;
}

void	path_set_length(t_path *path, int length)
{
	path->length = length;
}
