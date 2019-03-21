/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:12:11 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/21 16:43:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		matrix_mark_start(int **matrix, t_path *path)
{
	matrix[path->head->start_id][path->head->end_id] = path->head->end_len;
}

static void		matrix_mark_end(int **matrix, t_path *path)
{
	matrix[path->head->start_id][path->head->end_id] = path->head->start_len;
}

static int		**create_matrix(t_list *start_paths, t_list *end_paths)
{
	size_t	start_size;
	size_t	end_size;
	size_t	i;
	int		**matrix;

	start_size = start_paths->size;
	end_size = end_paths->size;
	i = 0;

	if (!(matrix = malloc(sizeof(*matrix) * start_size)))
		return (NULL);
	while (i < start_size)
	{
		matrix[i] = malloc(sizeof(int) * end_size);
		ft_bzero(matrix[i], sizeof(int) * end_size);
		i++;
	}
	return (matrix);
}

int		**get_paths_matrix(t_list *start_paths, t_list *end_paths)
{
	int		**matrix;
	t_node	*start_ptr;
	t_node	*end_ptr;

	if (!(matrix = create_matrix(start_paths, end_paths)))
		return (NULL);
	start_ptr = start_paths->head;
	while (start_ptr)
	{
		matrix_mark_start(matrix, *(t_path**)start_ptr->data);
		end_ptr = end_paths->head;
		while (end_ptr)
		{
			if ((*(t_path**)end_ptr->data)->head->start_id
					== (int)(*(t_path**)start_ptr->data)->path_id)
				matrix_mark_end(matrix, *(t_path**)end_ptr->data);
			end_ptr = end_ptr->next;
		}
		start_ptr = start_ptr->next;
	}
	return (matrix);
}
