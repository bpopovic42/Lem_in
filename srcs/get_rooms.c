/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/14 18:12:03 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static t_room	*new_room(char *name, char *com, t_links *links, t_pos *coord)
{
	t_room	*new_room;

	if (!(new_room = malloc(sizeof(*new_room))))
		exit(-1);
	new_room->comment = ft_strdup(com);
	new_room->name = ft_strdup(name);
	new_room->links = links;
	new_room->pos = *coord;
	return (new_room);
}

static void		record_room(t_graph *graph, char **room_data, char *comment)
{
	t_pos	coord;
	t_room	*room;
	t_hash	*new_hash;

	coord.x = ft_atoi(room_data[1]);
	coord.y = ft_atoi(room_data[2]);
	room = new_room(room_data[0], comment, NULL, &coord);
	new_hash = ft_hashnew(room->name, room, sizeof(*room));
	ft_hashpush(graph->rooms, new_hash);
	if (comment)
	{
		if (!(ft_strcmp(comment, "##start")))
			graph->start = room;
		else if (!(ft_strcmp(comment, "##end")))
			graph->end = room;
	}
}

int		get_rooms(char **input, t_graph *graph)
{
	int		i;
	char	*comment_ptr;
	char	**tmp;

	i = 0;
	comment_ptr = NULL;
	graph->rooms = ft_hash_newtable(100);
	/* While lines contains 3 words and/or starts by a '#'*/
	while (input[i++])
	{
		if (!(ft_count_words(input[i], WSPCS) == 3 || *input[i] == '#'))
		{
			if (ft_count_words(input[i], WSPCS) == 1 && i > 1 && ft_strchr(input[i], '-'))
				break;
			else
				return (-1);
		}
		/* If line is a comment keep a pointer to it */
		else if (*input[i] == '#')
			comment_ptr = input[i];
		/* Else line must be a room definition or end of array*/
		else if (input[i])
		{
			tmp = ft_strsplit(input[i], WSPCS);
			record_room(graph, tmp, comment_ptr);
			ft_delarray(tmp);
			comment_ptr = NULL;
		}
	}
	return (0);
}
