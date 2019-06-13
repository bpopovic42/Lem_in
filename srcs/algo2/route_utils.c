/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:06:21 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/13 20:29:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_route(t_route *route)
{
	ft_bzero(route, sizeof(*route));
	if (!(route->paths = ft_lstnew()))
		return (-1);
	return (0);
}

void	free_route(t_route *route)
{
	if (route)
	{
		if (route->score)
			free_score(&route->score);
		if (route->paths)
			ft_lstdel(route->paths, (void*)&free_path_from_node);
		ft_bzero(route, sizeof(*route));
	}
}
