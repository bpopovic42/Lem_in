/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/25 15:13:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static void		parse_command(char *line, char **cmd)
{
	if (line && line[1] == '#')
	{
		if (*cmd)
			ft_strdel(cmd);
		if (!(*cmd = ft_strdup(line)) && line)
			exit(-1);
	}
}

static int		parse_line(const char *line, char **cmd, t_graph *graph)
{
	if (line[0] == 'L')
	{
		lemin_perror("Line beginning by 'L'.");
		return (-1);
	}
	else if (ft_count_words(line, WSPCS) == 1 && ft_strchr(line, '-'))
		return (0); //parse link
	else if (ft_count_words(line, WSPCS) == 3)
	{
		if (create_room_if_valid(ft_strsplit(line, WSPCS), cmd, graph) < 0)
			return (-1);
	}
	return (0);
}

int				parse_input(int *ants, t_graph *graph)
{
	int		ret;
	char	*line;
	char	*cmd;

	ret = 0;
	cmd = NULL;
	while (ret >= 0 && (ret = get_next_line(STDIN, &line)) > 0)
	{
		if (!*ants)
			ret = get_ants_nbr(line, ants);
		else if (*line == '#')
			parse_command(line, &cmd);
		else
			ret = parse_line(line, &cmd, graph);
		if (ret >= 0)
			ft_putendl(line);
		ft_strdel(&line);
	}
	//ft_strdel(&line);
	return (ret);
}
