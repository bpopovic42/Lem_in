/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/19 19:11:59 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

int parse_input(unsigned int *ants_nbr, t_graph *graph)
{
	int		ret;
	char	*line;
	int		line_count;
	char	*comment_ptr;

	ret = 0;
	line = NULL;
	line_count = 0;
	comment_ptr = NULL;
	init_graph(graph);
	graph->room_list = ft_vector_init(sizeof(char*), 0);
	graph->rooms = ft_hash_newtable(100);
	while ((ret = get_next_line(STDIN, &line)) > 0)
	{
		if (line_count == 0)
		{
			if (get_ants_nbr(&line, ants_nbr) < 0)
				return (-1);
		}
		else if (line[0] == '#')
			comment_ptr = ft_strdup(line);
		else if (ft_count_words(line, WSPCS) == 3)
		{
			if (get_room(line, comment_ptr, graph) < 0)
				return (-1);
			comment_ptr = NULL;
		}
		else if (ft_count_words(line, WSPCS) == 1 && ft_strchr(line, '-'))
			ft_putstr_fd(line, 1);
		//	get_link();
		else
			return (-1);
		line_count++;
	}
	return (0);
}
