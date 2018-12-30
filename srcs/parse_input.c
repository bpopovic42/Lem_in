/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/30 19:48:38 by bopopovi         ###   ########.fr       */
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

static t_cmd	*new_command(const char *command, const char *room_name)
{
	t_cmd *new;

	if (!(new = malloc(sizeof(t_cmd*))))
		exit(-1);
	if (command)
		new->command = ft_strdup(command);
	else
		new->command = NULL;
	if (room_name)
		new->room_name = ft_strdup(room_name);
	else
		new->room_name = NULL;
	return (new);
}

static int		command_conflict(t_graph *graph, char *cmd)
{
	t_cmd	*ptr;
	size_t	i;

	i = 0;
	if (!cmd || !graph->command_list)
		return (0);
	while (i < graph->command_list->size)
	{
		ptr = ft_vector_get(graph->command_list, i);
		if (ptr && ptr->command)
		{
			if (!(ft_strcmp(cmd, ptr->command)))
				return (1);
		}
		i++;
	}
	return (0);
}


static int		get_cmd(t_graph *graph, char *line)
{
	t_cmd *ptr;

	ptr = ft_vector_get(graph->command_list, graph->command_list->size);
	if ((!ptr || ptr->room_name) && !command_conflict(graph, line))
	{
		ptr = new_command(line, NULL);
		ft_vector_append(graph->command_list, ptr);
		return (0);
	}
	return (local_exit(-1, "Command overwrite.", NULL));
	// Recuperer derniere commande
	// Si pas de commande ou derniere commande possede correspondance -> SAVE new command
	// Sinon SI derniere commande et derniere commande n'a pas de correspondance -> ERREUR
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
	if (data_missing(graph) && ret >= 0)
		ret = -1;
	return (local_exit(ret, NULL, cmd));
}
