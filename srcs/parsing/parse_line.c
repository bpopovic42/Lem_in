/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:14:02 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/22 17:36:22 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	get_ants(const char *input, int *ants)
{
	int tmp;

	if (!ft_is_valid_int(input) || ft_strchr(input, '-'))
	{
		print_warning("Invalid ants value : '%s'", input);
		return (1);
	}
	if ((tmp = ft_atoi(input)) <= 0)
	{
		print_warning("Invalid ants value : '%s'", input);
		return (1);
	}
	*ants = tmp;
	return (0);
}

static int	line_has_illegal_character(const char *line)
{
	if (line && line[0] == 'L')
	{
		print_warning("Line starting with 'L' : '%s'", line);
		return (1);
	}
	return (0);
}

static int	room_definition_is_over(t_graph *graph, const char *line)
{
	if (graph->nbr_of_links > 0)
	{
		print_warning("Room definition in links : '%s'", line);
		return (1);
	}
	return (0);
}

static int	handle_parsing_error(t_graph *graph, const char *line)
{
	if (graph->last_command)
		print_warning("Command before a link : '%s'", line);
	else
		print_warning("Failed to parse line : '%s'", line);
	return (1);
}

int			parse_line(t_graph *graph, int *ants, const char *line, char **cmds)
{
	if (line_has_illegal_character(line))
		return (1);
	else if (!line_is_comment(line))
	{
		if (line_is_command(line) && *ants > 0)
			return (parse_command(graph, line, cmds));
		else if (!(*ants))
			return (get_ants(line, ants));
		else if (line_is_room(line))
		{
			if (room_definition_is_over(graph, line))
				return (1);
			return (parse_room(graph, line));
		}
		else if (line_is_link(line) && !graph->last_command)
			return (parse_link(graph, line));
		else
			return (handle_parsing_error(graph, line));
	}
	return (0);
}
