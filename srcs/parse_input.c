/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/28 20:04:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static int		local_exit(int retval, char *msg, char *cmd)
{
	if (cmd)
		ft_strdel(&cmd);
	if (msg)
		lemin_perror(msg);
	return (retval);
}

static int		data_missing(t_graph *graph)
{
	if (!graph->nbr_of_rooms)
		return (local_exit(1, "No rooms provided.", NULL));
	else if (!graph->nbr_of_links)
		return (local_exit(1, "No links provided.", NULL));
	else if (!graph->start || !graph->end)
		return (local_exit(1, "Missing start and/or end room.", NULL));
	return (0);
}

static int		get_ants(char *input, int *ants)
{
	if (!ft_is_valid_int(input))
		return (local_exit(-1, "Invalid ants integer representation.", NULL));
	if (*input == '-' || (*ants = ft_atoi(input)) <= 0)
		return (local_exit(-1, "Invalid ants integer value.", NULL));
	return (0);
}

static void		get_cmd(char *line, char **cmd)
{
	if (*cmd)
		ft_strdel(cmd);
	*cmd = ft_strdup(line);
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
				get_cmd(line, &cmd);
			else if (*ants == 0)
				ret = get_ants(line, ants);
			else
				ret = parse_line(graph, line, &cmd);
		}
		ft_strdel(&line);
	}
	if (ret >= 0)
		ret = data_missing(graph) ? -1 : ret;
	return (local_exit(ret, NULL, cmd));
}
