/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:14:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/21 20:08:53 by bopopovi         ###   ########.fr       */
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
	else if (*cmd_list && ft_strstr(*cmd_list, line))
		return (1);
	if (!(graph->last_command = ft_strdup(line)))
		return (-1);
	if (!(*cmd_list = ft_strappendn(*cmd_list, 2, line, "\n")))
		return (-1);
	return (0);
}

int		parse_line(t_graph *graph, int *ants, const char *line, char **cmd_list)
{
	char **split;

	split = NULL;
	if (line[0] == 'L')
		return (1);
	else if (!(*line == '#' && *(line + 1) != '#'))
	{
		if (*ants > 0 && *line == '#' && line[1] == '#')
			return (get_cmd(graph, line, cmd_list));
		else if (*ants == 0)
			return (get_ants(line, ants));
		else if (is_room(line))
		{
			if (!(split = ft_strsplit(line, WSPCS)))
				return (-1);
			return (record_room_if_valid(graph, split));
		}
		else if (is_link(line) && !graph->last_command)
			return (record_link_if_valid(graph, line));
		else
			return (1);
	}
	return (0);
}
