/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:52:17 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/29 20:47:23 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	record_command(t_graph *graph, char **cmd_list, const char *cmd)
{
	if (!(graph->last_command = ft_strdup(cmd)))
		return (-1);
	if (!(*cmd_list = ft_strappendn(*cmd_list, 2, cmd, "\n")))
		return (-1);
	return (0);
}

static int	command_already_exist(const char *cmd, char **cmd_list)
{
	return (*cmd_list && ft_strnstr(*cmd_list, cmd, ft_strlen(*cmd_list)));
}

int			parse_command(t_graph *graph, const char *cmd, char **cmd_list)
{
	if (graph->last_command || command_already_exist(cmd, cmd_list))
		return (1);
	if (record_command(graph, cmd_list, cmd) < 0)
		return (-1);
	return (0);
}
