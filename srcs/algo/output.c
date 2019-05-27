/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:06:36 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 01:57:43 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	add_remaining_ants_to_paths(t_output *out, int ants, int diff)
{
	int		div_ants;
	int		surplus;
	int		i;

	div_ants = (ants - diff) / out->nbr_of_paths;
	surplus = (ants - diff) % out->nbr_of_paths;
	i = 0;
	while (i < out->nbr_of_paths)
	{
		out->paths[i]->ants += div_ants;
		if (surplus)
		{
			out->paths[i]->ants += 1;
			surplus--;
		}
		i++;
	}
}

int		set_path(t_output *out, int index, t_room *src, int *diff)
{
	if (!(out->paths[index] = ft_memalloc(sizeof(t_path))))
		return (-1);
	out->paths[index]->src = src;
	out->paths[index]->ants = out->longest_path_len - src->solution_len;
	*diff += out->paths[index]->ants;
	return (0);
}

int		get_paths(t_output *out, int ants, t_room *start)
{
	int		i;
	int		diff;
	t_room	*room_ptr;
	t_node	*node_ptr;

	i = 0;
	diff = 0;
	room_ptr = NULL;
	node_ptr = start->links->head;
	if (!(out->paths = ft_memalloc(sizeof(t_path*) * out->nbr_of_paths)))
		return (-1);
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->is_solution || room_is_end(room_ptr))
		{
			if (set_path(out, i, room_ptr, &diff) < 0)
				return (-1);
			i++;
		}
		node_ptr = node_ptr->next;
	}
	add_remaining_ants_to_paths(out, ants, diff);
	return (0);
}

void	print_ants_route(t_output *out, int ants, t_room *end)
{
	int i;
	int ants_count;
	int first_ant;

	ants_count = 1;
	while (end->ant < ants)
	{
		i = 0;
		first_ant = 1;
		while (i < out->nbr_of_paths)
		{
			move_ants(out->paths[i], &ants_count, &first_ant);
			i++;
		}
		ft_putchar('\n');
	}
}

int		print_ants(int ants, t_room *start, t_room *end)
{
	t_output *out;

	if (!(init_output(&out)))
		return (-1);
	if (get_output_data(out, start) < 0)
		return (-1);
	if (out->nbr_of_paths > 0)
	{
		get_paths(out, ants, start);
		print_ants_route(out, ants, end);
		free_output(&out);
		return (0);
	}
	free_output(&out);
	lemin_perror(ENOPATH, NULL);
	return (1);
}
