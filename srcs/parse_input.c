/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/26 19:32:01 by bopopovi         ###   ########.fr       */
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
	else if (ft_count_words(line, WSPCS) == 1 && ft_strchrn(line, '-') == 1)
	{
		if (*cmd)
		{
			lemin_perror("Command before link.");
			return (-1);
		}
		return (0); //parse link
	}
	else if (ft_count_words(line, WSPCS) == 3)
	{
		if (record_room_if_valid(ft_strsplit(line, WSPCS), cmd, graph) < 0)
			return (-1);
		return (0);
	}
	lemin_perror("Invalid line.");
	return (-1);
}

int				is_comment(char *line)
{
	return (*line == '#' && *(line + 1) != '#');
}

int				is_command(char *line)
{
	return (*line == '#' && *(line + 1) == '#');
}

int				parse_input(int *ants, t_graph *graph, char **file)
{
	int		ret;
	char	*line;
	char	*cmd;

	ret = 0;
	cmd = NULL;
	while (ret >= 0 && (ret = get_next_line(STDIN, &line)) > 0)
	{
		if (!*ants && !is_comment(line))
			ret = get_ants_nbr(line, ants);
		else if (is_command(line))
			parse_command(line, &cmd);
		else if (!is_comment(line))
			ret = parse_line(line, &cmd, graph);
		if (ret >= 0)
		{
			*file = ft_strappend(*file, line);
			*file = ft_strappend(*file, "\n");
		}
		ft_strdel(&line);
	}
	ft_strdel(&line); // GNL leaks to fix
	if (cmd)
		ft_strdel(&cmd);
	return (ret);
}
