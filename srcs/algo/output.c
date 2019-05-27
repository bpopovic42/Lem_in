/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:06:36 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/27 19:32:22 by bopopovi         ###   ########.fr       */
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

int		get_paths(t_output *out, int ants, t_room *start)
{
	t_node	*node_ptr;
	t_room	*room_ptr;
	int		i;
	int		diff;

	room_ptr = NULL;
	diff = 0;
	i = 0;
	node_ptr = start->links->head;
	if (!(out->paths = ft_memalloc(sizeof(t_path*) * out->nbr_of_paths)))
		return (-1);
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->is_solution || room_is_end(room_ptr))
		{
			if (!(out->paths[i] = ft_memalloc(sizeof(t_path))))
				return (-1);
			out->paths[i]->src = room_ptr;
			out->paths[i]->ants = out->longest_path_len - room_ptr->solution_len;
			diff += out->paths[i]->ants;
			i++;
		}
		node_ptr = node_ptr->next;
	}
	add_remaining_ants_to_paths(out, ants, diff);
	return (0);
}

void	move_ant_to_next_room(t_room *room)
{
	if (room->ant)
	{
		ft_printf("L%d-%s ", room->ant, room->solution_to->name);
		if (room_is_end(room->solution_to))
			room->solution_to->ant++;
		else
			room->solution_to->ant = room->ant;
		if (!room_is_end(room))
			room->ant = 0;
	}
}

void	move_new_ant_to_path(t_path *path, int *ants_count)
{
	t_room *ptr;

	ptr = path->src;
	if (path->ants > 0)
	{
		if (room_is_end(ptr))
			ptr->ant++;
		else
			ptr->ant = (*ants_count)++;
		path->ants--;
		ft_printf("L%d-%s ", ptr->ant, ptr->name);
	}
}

void	advance_path(t_path *path, int *ants_count)
{
	t_room *ptr;

	if (!path->last_ant)
		path->last_ant = path->src;
	ptr = path->last_ant;
	if (room_is_end(path->src))
	{
		move_new_ant_to_path(path, ants_count);
		return;
	}
	if (ptr == path->src && ptr->ant > 0 && ptr->solution_to->ant == 0 && !room_is_end(ptr->solution_to))
		move_ant_to_next_room(ptr);
	//ft_printf("from %s %d\n", ptr->name, path->ants);
	while (ptr && !room_is_start(ptr))
	{
		if (ptr->ant == 0 && ptr != path->src)
			break;
		if (ptr != path->src)
			move_ant_to_next_room(ptr);
		else
		{
			if (ptr->ant > 0)
				move_ant_to_next_room(ptr);
			move_new_ant_to_path(path, ants_count);
		}
		ptr = ptr->solution_from;
	}
	if (!room_is_end(path->last_ant->solution_to) && path->last_ant->solution_to->ant > 0)
		path->last_ant = path->last_ant->solution_to;
}

void	print_ants_route(t_output *out, int ants, t_room *end)
{
	int i;
	int ants_count;

	ants_count = 1;
	while (end->ant < ants)
	{
		i = 0;
		while (i < out->nbr_of_paths)
		{
			advance_path(out->paths[i], &ants_count);
			i++;
		}
		//ft_printf("[ end ants : %d ]\n", end->ant);
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
