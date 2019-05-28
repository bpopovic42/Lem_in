/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 18:07:53 by bopopovi         ###   ########.fr       */
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

void	file_data_append(char *d, size_t d_size, char *l, size_t l_size)
{
	size_t i;

	i = 0;
	while (i < l_size)
	{
		d[d_size + i] = l[i];
		i++;
	}
	d[d_size + i] = '\n';
}

int		file_append_buffer(t_file *file, char *line)
{
	char	*new_data;
	size_t	line_size;
	size_t	new_capacity;

	new_data = NULL;
	new_capacity = file->capacity;
	line_size = ft_strlen(line);
	if (line_size + file->size + 1 >= file->capacity)
	{
		while (new_capacity < (line_size + file->size + 1))
			new_capacity *= 2;
		if (!(new_data = ft_strnew(new_capacity)))
			return (-1);
		file->capacity = new_capacity;
		ft_strncpy(new_data, file->data, file->size);
		ft_strdel(&file->data);
		file->data = new_data;
	}
	file_data_append(file->data, file->size, line, line_size);
	file->size += line_size + 1;
	return (0);
}

int		parse_input(int *ants, t_graph *graph, t_file *file)
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
			break;
		if (file_append_buffer(file, line) < 0)
		{
			error_status = -1;
			break;
		}
		ft_strdel(&line);
	}
	if (error_status < 0)
		return (local_exit(line, cmd_list, error_status));
	else if ((error_status = check_input(*ants, graph)) > 0)
		lemin_perror(error_status, line);
	return (local_exit(line, cmd_list, error_status));
}
