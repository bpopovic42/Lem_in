/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/24 01:04:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static void parse_command(char *line, char **command)
{
	if (line && line[1] == '#')
	{
		if (*command != NULL)
			ft_strdel(command);
		if (!(*command = ft_strdup(line)))
		{
			lemin_perror("get_command: ft_strdup failure.", 1);
			exit(-1);
		}
	}
}

static int	parse_line(const char *line, char **cmd, t_graph *graph)
{

	if (line[0] == 'L')
		return (-1);
	else if (ft_count_words(line, WSPCS) == 1 && ft_strchr(line, '-'))
		return (0); //parse link
	else if (ft_count_words(line, WSPCS) == 3)
	{
		if (create_room_if_valid((char*)line, cmd, graph) < 0)
			return (-1);
	}
	return (0);
}

int parse_input(unsigned int *ants, t_graph *graph)
{
	int		ret;
	char	*line;
	char	*command;

	ret = 0;
	line = NULL;
	command = NULL;
	while (ret >= 0 && (ret = get_next_line(STDIN, &line)) > 0)
	{
		if (*ants == 0)
			ret = get_ants_nbr(line, ants);
		else if (line[0] == '#')
			parse_command(line, &command);
		else
			ret = parse_line(line, &command, graph);
		if (ret >= 0)
			ft_putendl(line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (ret);
}
