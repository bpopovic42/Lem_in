/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:12:11 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/20 19:24:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void		matrix_mark_start(int **matrix, t_path *path)
{
	matrix[path->head->start_id][path->head->end_id] = path->head->end_len;
}

static void		matrix_mark_end(int **matrix, t_path *path)
{
	matrix[path->head->start_id][path->head->end_id] = path->head->start_len;
}

int		**get_paths_matrix(t_list *start_paths, t_list *end_paths)
{
	int		**paths_matrix;
	t_node	*current;
	t_node	*ptr;

	paths_matrix = (int**)ft_new_array(start_paths->size, end_paths->size, sizeof(int));
	current = start_paths->head;
	while (current)
	{
		matrix_mark_start(paths_matrix, *(t_path**)current->data);
		ptr = end_paths->head;
		while (ptr)
		{
			if ((*(t_path**)ptr->data)->head->start_id == (int)(*(t_path**)current->data)->path_id)
				matrix_mark_end(paths_matrix, *(t_path**)ptr->data);
			ptr = ptr->next;
		}
		current = current->next;
	}
	return (paths_matrix);
}
