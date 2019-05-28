/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room_if_valid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:39:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 20:15:09 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*create_room(char **room_data)
{
	t_pos	coord;
	t_room	*room;

	coord.x = ft_atoi(room_data[1]);
	coord.y = ft_atoi(room_data[2]);
	if (!(room = new_room(room_data[0], &coord)))
		return (NULL);
	return (room);
}

static int		room_data_is_valid(char **room_data)
{
	char *room_name;
	char *x;
	char *y;

	room_name = room_data[0];
	x = room_data[1];
	y = room_data[2];
	if (ft_strchr(room_name, '-'))
		return (0);
	else if (!ft_is_valid_int(x) || !ft_is_valid_int(y))
		return (0);
	else if (ft_atoi(x) < 0 || ft_atoi(y) < 0)
		return (0);
	return (1);
}

int				create_room_if_valid(char **room_data, t_room **room)
{
	if (!room_data_is_valid(room_data))
		return (1);
	if (!((*room) = create_room(room_data)))
		return (-1);
	return (0);
}
