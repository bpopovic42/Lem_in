/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/01/04 18:29:57 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static int		get_ants(char *input, int *ants)
{
	int tmp;

	if (!ft_is_valid_int(input))
		return (-1);
	tmp = ft_atoi(input);
	if (*input == '-' || tmp <= 0)
		return (-1);
	*ants = tmp;
	return (0);
}

static int		get_cmd(t_graph *graph, char *line, char **cmd_list)
{
	if (graph->last_command)
		return (-1);
	else if (*cmd_list && ft_strstr(*cmd_list, line))
		return (-1);
	graph->last_command = ft_strdup(line);
	*cmd_list = ft_strappendn(*cmd_list, 2, line, "\n");
	return (0);
}

char	*parse_input(int *ants, t_graph *graph, char **file)
{
	int		ret;
	char	*cmd_list;
	char	*line;

	ret = 1;
	cmd_list = NULL;
	line = NULL;
	while (ret >= 0 && (ret = get_next_line(STDIN, &line)) > 0)
	{
		if (ret > 0 && !(*line == '#' && *(line + 1) != '#'))
		{
			if (*ants > 0 && *line == '#' && line[1] == '#')
				ret = get_cmd(graph, line, &cmd_list);
			else if (*ants == 0)
				ret = get_ants(line, ants);
			else
				ret = parse_line(graph, line);
		}
		if (ret >= 0)
		{
			*file = ft_strappendn(*file, 2, line, "\n");
			ft_strdel(&line);
		}
	}
	ft_strdel(&cmd_list);
	return (line);
}
