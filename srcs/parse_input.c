/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/01/04 16:42:43 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static int		local_exit(int error_status, char *cmd)
{
	if (cmd)
		ft_strdel(&cmd);
	return (error_status);
}

static int		get_ants(char *input, int *ants)
{
	int tmp;

	if (!ft_is_valid_int(input))
		return (local_exit(-1, NULL));
	tmp = ft_atoi(input);
	if (*input == '-' || tmp <= 0)
		return (local_exit(-1, NULL));
	*ants = tmp;
	return (0);
}

static int		get_cmd(t_graph *graph, char *line)
{
	if (graph->last_command)
		return (local_exit(-1, NULL));
	else
		graph->last_command = ft_strdup(line);
	return (0);
}

int				parse_input(int *ants, t_graph *graph, char **file)
{
	int		ret;
	char	*cmd;
	char	*line;

	ret = 1;
	cmd = NULL;
	line = NULL;
	while (ret >= 0 && (ret = get_next_line(STDIN, &line)) > 0)
	{
		*file = ft_strappendn(*file, 2, line, "\n");
		if (ret > 0 && !(*line == '#' && *(line + 1) != '#'))
		{
			if (*ants > 0 && *line == '#' && line[1] == '#')
				ret = get_cmd(graph, line);
			else if (*ants == 0)
				ret = get_ants(line, ants);
			else
				ret = parse_line(graph, line);
		}
		ft_strdel(&line);
	}
	return (local_exit(ret, cmd));
}
