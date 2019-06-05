/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:06:36 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/05 19:14:08 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	add_remaining_ants_to_paths(t_output *out, int ants, int diff)
{
	int		div_ants;
	int		surplus;
	t_node	*node_ptr;
	t_path	*path_ptr;

	div_ants = (ants - diff) / out->paths->size;
	surplus = (ants - diff) % out->paths->size;
	node_ptr = out->paths->head;
	while (node_ptr)
	{
		path_ptr = *(t_path**)node_ptr->data;
		path_ptr->ants += div_ants;
		if (surplus)
		{
			path_ptr->ants += 1;
			surplus--;
		}
		node_ptr = node_ptr->next;
	}
}

void	set_path(t_output *out, t_path *path, int *diff)
{
	path->ants = out->longest_path_len - path->head->solution_len;
	*diff += path->ants;
}

int		set_paths(t_output *out, int ants)
{
	int		diff;
	t_path	*path_ptr;
	t_node	*node_ptr;

	diff = 0;
	path_ptr = NULL;
	node_ptr = out->paths->head;
	while (node_ptr)
	{
		path_ptr = *(t_path**)node_ptr->data;
		set_path(out, path_ptr, &diff);
		node_ptr = node_ptr->next;
	}
	add_remaining_ants_to_paths(out, ants, diff);
	return (0);
}

void	print_ants_route(t_output *out, int ants, t_room *end)
{
	int ants_count;
	int first_ant;
	t_node *node_ptr;
	t_path *path_ptr;

	ants_count = 1;
	while (end->ant < ants)
	{
		first_ant = 1;
		node_ptr = out->paths->head;
		while (node_ptr)
		{
			path_ptr = *(t_path**)node_ptr->data;
			move_ants(path_ptr, &ants_count, &first_ant);
			node_ptr = node_ptr->next;
		}
		ft_putchar('\n');
	}
}

int		print_ants(int ants, t_list *paths, t_room *end)
{
	t_output *out;

	if (!(init_output(&out)))
		return (-1);
	out->paths = paths;
	get_output_data(out);
	set_paths(out, ants);
	print_ants_route(out, ants, end);
	free_output(&out);
	return (0);
	//lemin_perror(ENOPATH, NULL);
}
