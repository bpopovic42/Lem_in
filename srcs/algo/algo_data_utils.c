/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:40:41 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/06 20:41:17 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*get_path_from_node(t_node *path_container)
{
	if (path_container && path_container->data)
		return (*(t_path**)path_container->data);
	return (NULL);
}
