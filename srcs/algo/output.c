/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:06:36 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/22 16:42:26 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

int		get_paths(t_output *out, int ants, t_room *start)
{
	t_node	*node_ptr;
	t_room	*room_ptr;
	int		surplus;
	int		div_ants;
	int		i;
	int		diff;

	room_ptr = NULL;
	diff = 0;
	i = 0;
	surplus = 0;
	node_ptr = start->links->head;
	if (!(out->paths = ft_memalloc(sizeof(t_path*) * out->nbr_of_paths)))
		return (-1);
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->solution_to || room_is_end(room_ptr))
		{
			if (!(out->paths[i] = ft_memalloc(sizeof(t_path))))
				return (-1);
			out->paths[i]->last_ant = NULL;
			out->paths[i]->src = room_ptr;
			out->paths[i]->ants = out->longest_path_len - room_ptr->solution_len;
			diff += out->paths[i]->ants;
			i++;
		}
		node_ptr = node_ptr->next;
	}
	//ft_printf("Diff %d\n", diff);
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
		//ft_printf("for path %s of len %d, %d ants\n", out->paths[i]->src->name, out->paths[i]->src->solution_len, out->paths[i]->ants);
		i++;
	}
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
		room->ant = 0;
	}
	else
		ft_printf("ABNORMAL BEHAVIOR\n");
}

void	advance_path(t_path *path, int *ants_count)
{
	t_room *ptr;

	if (!path->last_ant)
		path->last_ant = path->src;
	ptr = path->last_ant;
	//ft_printf("from %s %d\n", ptr->name, path->ants);
	while (ptr && !room_is_start(ptr))
	{
		move_ant_to_next_room(ptr);
		if (ptr == path->src)
		{
			if (path->ants > 0)
			{
				ptr->ant = (*ants_count)++;
				path->ants--;
				ft_printf("L%d-%s ", ptr->ant, ptr->name);
			}
			//else
			//	break;
		}
		/*else if (ptr->solution_from && ptr->solution_from->ant > 0)
		{
			ft_printf("L%d-%s ", ptr->solution_from->ant, ptr->name);
			ptr->ant = ptr->solution_from->ant;
			ptr->solution_from->ant = 0;
		}*/

		//if (ptr->solution_from && ptr->solution_from->ant == 0 && ptr->ant == 0 && ptr != path->src)
		//	break;
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
		ft_printf("end ants : %d\n", end->ant);
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
