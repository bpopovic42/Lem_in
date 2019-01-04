/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/01/04 20:44:14 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static int	check_input(int ants, t_graph *graph, char *last_line)
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
	if (error_status)
	{
		lemin_perror(error_status, last_line);
		return (-1);
	}
	return (0);
}

int		parse_input(int *ants, t_graph *graph, char **file)
{
	int		ret;
	char	*cmd_list;
	char	*line;

	ret = 1;
	cmd_list = NULL;
	line = NULL;
	while ((ret = get_next_line(STDIN, &line)) > 0)
	{
		if (parse_line(graph, ants, line, &cmd_list) < 0)
			break ;
		*file = ft_strappendn(*file, 2, line, "\n");
		ft_strdel(&line);
	}
	if (ret >= 0 && (ret = check_input(*ants, graph, line)) < 0 && line)
		ft_strdel(&line);
	return (ret);
}
