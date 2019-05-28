/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:14:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 19:10:19 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		get_ants(const char *input, int *ants)
{
	int tmp;

	if (!ft_is_valid_int(input))
		return (1);
	tmp = ft_atoi(input);
	if (*input == '-' || tmp <= 0)
		return (1);
	*ants = tmp;
	return (0);
}

static int		get_cmd(t_graph *graph, const char *line, char **cmd_list)
{
	if (graph->last_command)
		return (1);
	else if (*cmd_list && ft_strnstr(*cmd_list, line, ft_strlen(line)))
		return (1);
	if (!(graph->last_command = ft_strdup(line)))
		return (-1);
	if (!(*cmd_list = ft_strappendn(*cmd_list, 2, line, "\n")))
		return (-1);
	return (0);
}

int		parse_line(t_graph *graph, int *ants, const char *line, char **cmd_list)
{
	if (line[0] == 'L')
		return (1);
	else if (!line_is_comment(line))
	{
		if (line_is_command(line) && *ants > 0)
			return (get_cmd(graph, line, cmd_list));
		else if (!(*ants))
			return (get_ants(line, ants));
		else if (line_is_room(line))
			return (record_room_if_valid(graph, line));
		else if (line_is_link(line) && !graph->last_command)
			return (record_link_if_valid(graph, line));
		else
			return (1);
	}
	return (0);
}
