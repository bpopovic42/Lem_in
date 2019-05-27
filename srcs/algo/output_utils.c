/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:06:03 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/27 18:50:11 by bopopovi         ###   ########.fr       */
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

int		get_output_data(t_output *out, t_room *start)
{
	t_node *node_ptr;
	t_room *room_ptr;

	out->longest_path_len = -1;
	out->nbr_of_paths = 0;
	room_ptr = NULL;
	node_ptr = start->links->head;
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->is_solution || room_is_end(room_ptr))
		{
			out->nbr_of_paths++;
			if (room_ptr->solution_len > out->longest_path_len)
				out->longest_path_len = room_ptr->solution_len;
		}
		node_ptr = node_ptr->next;
	}
	return (0);
}

void	free_paths(t_path **paths, int nbr_of_paths)
{
	int i;

	i = 0;
	while (i < nbr_of_paths)
	{
		ft_bzero(paths[i], sizeof(paths[i]));
		free(paths[i]);
		i++;
	}
	ft_bzero(paths, sizeof(paths));
	free(paths);

}

void	free_output(t_output **output)
{
	if ((*output)->paths && (*output)->nbr_of_paths)
		free_paths((*output)->paths, (*output)->nbr_of_paths);
	ft_bzero(*output, sizeof(**output));
	free(*output);
}
