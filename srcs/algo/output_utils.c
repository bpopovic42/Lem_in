/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:06:03 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 19:05:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		init_output(t_output **output)
{
	if (((*output) = ft_memalloc(sizeof(**output))))
	{
		ft_bzero(*output, sizeof(**output));
		return (1);
	}
	return (-1);
}

int		get_longest_path_length(t_list *paths)
{
	int		longest_length;
	t_node	*node_ptr;
	t_path	*path_ptr;

	longest_length = -1;
	node_ptr = paths->head;
	path_ptr = NULL;
	while (node_ptr)
	{
		path_ptr = *(t_path**)node_ptr->data;
		if (path_ptr->head->solution_len > longest_length)
			longest_length = path_ptr->head->solution_len;
		node_ptr = node_ptr->next;
	}
	return (longest_length);
}

void	get_output_data(t_output *out)
{
	out->longest_path_len = get_longest_path_length(out->paths);
}

void	free_output(t_output **output)
{
	ft_bzero(*output, sizeof(**output));
	free(*output);
}
