/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_paths_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 15:32:51 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/07 15:35:16 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	update_path_length(t_node *path_container)
{
	t_path *path;

	path = get_path_from_node(path_container);
	path->length = path->head->end_distance;
}

void	update_paths_length(t_list *paths)
{
	ft_lstiter(paths, &update_path_length);
}
