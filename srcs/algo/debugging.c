/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:45:52 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/19 19:49:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	dbg_print_next_rooms(t_room *target, int from_start)
{
	size_t	i;
	int		*target_depth;
	t_room *ptr;

	i = 0;
	while (i < target->links->size)
	{
		ptr = ft_vector_get(target->links, i);
		target_depth = from_start ? &ptr->end_len : &ptr->start_len;
		ft_printf("Room '%s' depth = %d\n", ptr->name, *target_depth);
		i++;
	}
}

void	dbg_print_paths(t_list *path_list)
{
	t_tmp *tmp;
	t_node *ptr;

	ptr = path_list->head;
	while (ptr)
	{
		tmp = *(t_tmp**)ptr->data;
		ft_printf("Path %s of size %d\n", tmp->room->name, tmp->size);
		ptr = ptr->next;
	}
	ft_putchar('\n');
}

void	dbg_array_print(int **matrix, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			ft_printf("| %d |", matrix[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
