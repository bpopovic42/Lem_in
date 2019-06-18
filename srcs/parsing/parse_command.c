/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:52:17 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 20:27:44 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	record_command(t_graph *graph, char **cmds, const char *cmd)
{
	if (!(graph->last_command = ft_strdup(cmd)))
		return (-1);
	if (!(*cmds = ft_strappendn(*cmds, 2, cmd, "\n")))
		return (-1);
	return (0);
}

static int	command_already_exist(const char *cmd, char **cmds)
{
	return (*cmds && ft_strnstr(*cmds, cmd, ft_strlen(*cmds)));
}

int			parse_command(t_graph *graph, const char *cmd, char **cmds)
{
	if (graph->last_command || command_already_exist(cmd, cmds))
		return (1);
	if (record_command(graph, cmds, cmd) < 0)
		return (-1);
	return (0);
}
