/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:14:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/01/04 16:16:33 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		is_link(const char *line)
{
	return (ft_count_words(line, WSPCS) == 1 && ft_strchrn(line, '-') == 1);
}

static int		is_room(const char *line)
{
	return (ft_count_words(line, WSPCS) == 3);
}

int		parse_line(t_graph *graph, const char *line)
{
	if (line[0] == 'L')
		return (-1);
	else if (is_link(line))
	{
		if (graph->last_command)
			return (-1);
		return (record_link_if_valid(graph, line));
	}
	else if (is_room(line))
	{
		return (record_room_if_valid(graph, ft_strsplit(line, WSPCS)));
	}
	return (-1);
}
