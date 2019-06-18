/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 19:11:36 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/06 22:08:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		sort_by_end_distance(void *node_a, void *node_b)
{
	t_path *path_a;
	t_path *path_b;

	path_a = *(t_path**)node_a;
	path_b = *(t_path**)node_b;
	return (path_a->length < path_b->length);
}

void	assign_paths_ids(t_list *paths)
{
	int		i;
	t_path	*path_ptr;
	t_node	*node_ptr;

	i = 0;
	path_ptr = NULL;
	node_ptr = paths->head;
	while (node_ptr)
	{
		path_ptr = (*(t_path**)node_ptr->data);
		path_ptr->head->pid = i;
		node_ptr = node_ptr->next;
		i++;
	}
}

void	sort_paths_by_head_distance(t_list *paths)
{
	t_node	*node_ptr;
	t_path	*path_ptr;

	node_ptr = paths->head;
	while (node_ptr)
	{
		path_ptr = *(t_path**)node_ptr->data;
		path_ptr->length = path_ptr->head->end_distance;
		node_ptr = node_ptr->next;
	}
	ft_lstsort(paths, &sort_by_end_distance);
	assign_paths_ids(paths);
}
