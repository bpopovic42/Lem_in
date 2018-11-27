/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 18:41:55 by bopopovi          #+#    #+#             */
/*   Updated: 2018/11/27 19:40:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		get_rooms(char **input, t_graph *graph)
{
	int		i;
	char	*comment_ptr;
	(void)input;
	(void)graph;

	i = 1;
	comment_ptr = NULL;
	graph->rooms = ft_vector_init(sizeof(t_room), 0);
	/* While lines contains 3 words and/or starts by a '#'*/
	while (input[i] && (ft_count_words(input[i], WSPCS) == 3 || *input[i] == '#'))
	{
		/* If line is a comment */
		/* Save a pointer to it */
		ft_putnbr(ft_count_words(input[i], WSPCS));
		if (*input[i] == '#')
		{
			ft_printf("%s : %s\n", "Comment", input[i]);
			comment_ptr = input[i];
		}
		/* Else line must be a room definition */
		/* Call input recording function */
		else
		{
			ft_printf("%s : %s\n", "Room", input[i]);
		}
		i++;
	}
	return (0);
}
