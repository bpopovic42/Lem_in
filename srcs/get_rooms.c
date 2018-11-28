/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2018/11/28 19:51:51 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void		record_room(t_graph *graph, char **room, char *comment)
{
	t_room	*new_room;
	t_pos	*coord;

	if (!room)
		ft_putstr("no room");
	new_room = malloc(sizeof(*new_room));
	coord = malloc(sizeof(*coord));
	coord->x = ft_atoi(room[1]);
	coord->y = ft_atoi(room[2]);
	new_room->comment = ft_strdup(comment);
	new_room->name = ft_strdup(room[0]);
	new_room->links = NULL;
	new_room->position = coord;
	ft_vector_append(graph->rooms, new_room);
}

int		get_rooms(char **input, t_graph *graph)
{
	int		i;
	char	*comment_ptr;

	i = 1;
	comment_ptr = NULL;
	graph->rooms = ft_vector_init(sizeof(t_room), 0);
	/* While lines contains 3 words and/or starts by a '#'*/
	while (input[i] && (ft_count_words(input[i], WSPCS) == 3 || *input[i] == '#'))
	{
		/* If line is a comment */
		/* Save a pointer to it */
		if (*input[i] == '#')
			comment_ptr = input[i];
		/* Else line must be a room definition or end of array*/
		/* Call input recording function */
		else if (input[i])
		{
			record_room(graph, ft_strsplit(input[i], WSPCS), comment_ptr);
		}
		i++;
	}
	return (0);
}
