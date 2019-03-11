/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/11 19:19:22 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static int	local_exit(char *line, char *cmd_list, int retval)
{
	if (line)
		ft_strdel(&line);
	if (cmd_list)
		ft_strdel(&cmd_list);
	return (retval);
}

static int	check_input(int ants, t_graph *graph)
{
	int error_status;

	error_status = 0;
	if (ants <= 0)
		error_status = EINVANT;
	else if (graph->nbr_of_rooms < 2)
		error_status = ENEROOM;
	else if (graph->nbr_of_links < 1)
		error_status = ENELINK;
	else if (!graph->start || !graph->end)
		error_status = EINVMAP;
	return (error_status);
}

int		parse_input(int *ants, t_graph *graph, char **file)
{
	int		error_status;
	char	*cmd_list;
	char	*line;

	error_status = 0;
	cmd_list = NULL;
	line = NULL;
	while ((error_status = get_next_line(STDIN, &line)) > 0)
	{
		if ((error_status = parse_line(graph, ants, line, &cmd_list)) != 0)
			break ;
		*file = ft_strappendn(*file, 2, line, "\n");
		ft_strdel(&line);
	}
	if (error_status < 0)
		return (local_exit(line, cmd_list, error_status));
	else if ((error_status = check_input(*ants, graph)) > 0)
		lemin_perror(error_status, line);
	return (local_exit(line, cmd_list, error_status));
}
