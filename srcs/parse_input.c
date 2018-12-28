/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/28 14:14:20 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

int				is_comment(char *line)
{
	return (*line == '#' && *(line + 1) != '#');
}

int				is_command(char *line)
{
	return (*line == '#' && *(line + 1) == '#');
}

static void		get_command(char *line, char **cmd)
{
	if (*cmd)
		ft_strdel(cmd);
	*cmd = ft_strdup(line);
}

static int		get_ants(char *input, int *ants)
{
	if (!ft_is_valid_int(input))
	{
		lemin_perror("Invalid ants integer representation.");
		return (-1);
	}
	if (*input == '-' || (*ants = ft_atoi(input)) <= 0)
	{
		lemin_perror("Invalid ants integer value.");
		return (-1);
	}
	return (0);
}

int				parse_input(int *ants, t_graph *graph, char **file)
{
	int		ret;
	char	*cmd;
	char	*line;

	ret = 0;
	cmd = NULL;
	while (ret >= 0 && (ret = get_next_line(STDIN, &line)) > 0)
	{
		if (!*ants && !is_comment(line))
			ret = get_ants(line, ants);
		else if (is_command(line))
			get_command(line, &cmd);
		else if (!is_comment(line))
			ret = parse_line(graph, line, &cmd);
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
