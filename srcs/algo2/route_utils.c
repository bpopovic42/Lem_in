/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 20:06:21 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/06 22:21:56 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_route(t_route *route)
{
	ft_bzero(route, sizeof(*route));
	if (!(route->score = ft_memalloc(sizeof(*route->score))))
		return (-1);
	if (!(route->paths = ft_lstnew()))
		return (-1);
	return (0);
}

void	free_route(t_route *route)
{
	if (route)
	{
		if (route->score)
		{
			ft_bzero(route->score, sizeof(*route->score));
			ft_memdel((void**)&route->score);
		}
		if (route->paths)
			ft_lstdel(route->paths, (void*)&free_path);
		ft_bzero(route, sizeof(*route));
	}
}
