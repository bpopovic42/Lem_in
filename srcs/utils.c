/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:40:03 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/24 01:41:06 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_room(void *room)
{
	if (((t_room*)room)->comment != NULL)
		ft_strdel(&(((t_room*)room)->comment));
	ft_strdel(&(((t_room*)room)->name));
	//free(((t_room*)room)->links);
	((t_room*)room)->pos.x = 0;
	((t_room*)room)->pos.y = 0;
	free(room);
}
