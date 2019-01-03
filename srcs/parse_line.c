/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:14:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/01/03 18:07:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		local_exit(int retval, char *msg)
{
	if (msg)
		lemin_perror(msg);
	return (retval);
}

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
		return (local_exit(-1, "Line beginning by 'L'."));
	else if (is_link(line))
	{
		if (graph->last_command)
			return (local_exit(-1, "Command before link."));
		else if (record_link_if_valid(graph, line) >= 0)
			return (0);
		else
			return (-1);
	}
	else if (is_room(line))
	{
		if (record_room_if_valid(graph, ft_strsplit(line, WSPCS)) >= 0)
			return (0);
		else
			return (-1);
	}
	return (local_exit(-1, "Invalid line."));
}
