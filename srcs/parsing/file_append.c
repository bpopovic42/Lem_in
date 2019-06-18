/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:16:42 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 16:45:55 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	file_data_append(t_file *file, char *data, size_t data_size)
{
	ft_strncpy(file->data + file->size, data, data_size);
	file->data[file->size + data_size] = '\n';
}

static int	extend_file_capacity(t_file *file, size_t new_min_capacity)
{
	char	*new_data;
	size_t	new_capacity;

	new_data = NULL;
	new_capacity = file->capacity;
	while (new_capacity < new_min_capacity)
		new_capacity *= 2;
	if (!(new_data = ft_strnew(new_capacity)))
		return (-1);
	file->capacity = new_capacity;
	ft_strncpy(new_data, file->data, file->size);
	ft_strdel(&file->data);
	file->data = new_data;
	return (0);
}

int			file_append(t_file *file, char *line)
{
	size_t	line_size;
	size_t	new_file_size;

	line_size = ft_strlen(line);
	new_file_size = (line_size + file->size + 1);
	if (new_file_size >= file->capacity)
	{
		if (extend_file_capacity(file, new_file_size) < 0)
			return (-1);
	}
	file_data_append(file, line, line_size);
	file->size = new_file_size;
	return (0);
}
