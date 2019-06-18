/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_access_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 13:40:54 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 16:44:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*get_room_from_node(t_node *node)
{
	if (node && node->data)
		return (*(t_room**)node->data);
	return (NULL);
}

t_path	*get_path_from_node(t_node *path_container)
{
	if (path_container && path_container->data)
		return (*(t_path**)path_container->data);
	return (NULL);
}
