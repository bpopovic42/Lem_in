/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:14:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 20:26:44 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	get_ants(const char *input, int *ants)
{
	int tmp;

	if (!ft_is_valid_int(input) || ft_strchr(input, '-'))
		return (1);
	if ((tmp = ft_atoi(input)) <= 0)
		return (1);
	*ants = tmp;
	return (0);
}

int			parse_line(t_graph *graph, int *ants, const char *line, char **cmds)
{
	if (line[0] == 'L')
		return (1);
	else if (!line_is_comment(line))
	{
		if (line_is_command(line) && *ants > 0)
			return (parse_command(graph, line, cmds));
		else if (!(*ants))
			return (get_ants(line, ants));
		else if (line_is_room(line))
			return (parse_room(graph, line));
		else if (line_is_link(line) && !graph->last_command)
			return (parse_link(graph, line));
		else
			return (1);
	}
	return (0);
}
