/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/13 20:04:37 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void		record_room(t_graph *graph, char **room, char *comment)
{
	t_room	*new_room;
	t_pos	coord;
	t_hash	*new_hash;

	if (!room)
		ft_putstr("no room");
	coord.x = ft_atoi(room[1]);
	coord.y = ft_atoi(room[2]);
	if (!(new_room = malloc(sizeof(*new_room))))
		exit(-1);
	new_room->comment = ft_strdup(comment);
	new_room->name = ft_strdup(room[0]);
	new_room->links = NULL;
	new_room->pos = coord;
	new_hash = ft_hashnew(new_room->name, new_room, sizeof(*new_room));
	ft_hashpush(graph->rooms, new_hash);
	if (comment)
	{
		if (!(ft_strcmp(comment, "##start")))
			graph->start = new_room;
		else if (!(ft_strcmp(comment, "##end")))
			graph->end = new_room;
	}
}

int		get_rooms(char **input, t_graph *graph)
{
	int		i;
	char	*comment_ptr;
	char	**tmp;

	i = 1;
	comment_ptr = NULL;
	graph->rooms = ft_hash_newtable(100);
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
			tmp = ft_strsplit(input[i], WSPCS);
			record_room(graph, tmp, comment_ptr);
			ft_delarray(tmp);
			comment_ptr = NULL;
		}
		i++;
	}
	return (0);
}
