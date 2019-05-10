/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_solution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 13:22:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/09 21:09:15 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

t_room	*get_next_path(t_list *paths)
{
	t_node *ptr;
	t_room *shortest;

	ptr = paths->head;
	shortest = NULL;
	while (ptr)
	{
		if ((*(t_room**)ptr->data)->final_distance >= 0)
		{
			if (!shortest || (*(t_room**)ptr->data)->final_distance < shortest->final_distance)
			{
				if ((*(t_room**)ptr->data)->recorded == 0)
					shortest = (*(t_room**)ptr->data);
			}
		}
		ptr = ptr->next;
	}
	if (shortest)
		shortest->recorded = 1;
	return (shortest);
}

void	remove_solution_marks_from_path(t_room *src)
{
	t_room *room_ptr;
	t_room *previous_room_ptr;

	room_ptr = src->to;
	previous_room_ptr = src;
	while (previous_room_ptr && !room_is_end(previous_room_ptr))
	{
		previous_room_ptr->solution_to = NULL;
		previous_room_ptr->solution_from = NULL;
		previous_room_ptr = room_ptr;
		if (room_ptr && room_ptr->to)
			room_ptr = room_ptr->to;
	}
}

void	mark_solution_path(t_room *src)
{
	t_room *room_ptr;

	room_ptr = src;
	while (room_ptr && !room_is_end(room_ptr))
	{
		room_ptr->solution_from = room_ptr->from;
		room_ptr->solution_to = room_ptr->to;
		room_ptr = room_ptr->to;
	}
}

void	replace_previous_solution(t_list *start_rooms)
{
	t_node	*ptr;
	t_room	*room_ptr;

	ptr = start_rooms->head;
	while (ptr)
	{
		room_ptr = *(t_room**)ptr->data;
		if (room_ptr->solution_to != NULL)
			remove_solution_marks_from_path(room_ptr);
		if (room_ptr->solution_len >= 0)
		{
			mark_solution_path(room_ptr);
		}
		ptr = ptr->next;
	}
}

void	clean_previous_solution_marks(t_list *start_rooms)
{
	t_node	*node_ptr;
	t_room	*room_ptr;

	node_ptr = start_rooms->head;
	while (node_ptr)
	{
		room_ptr = *(t_room**)node_ptr->data;
		if (room_ptr->solution_len >= 0)
			room_ptr->solution_len = -1;
		node_ptr = node_ptr->next;
	}
}

int		compute_solution(t_list *start_rooms, int *solution, int ants)
{
	int paths;
	int new_solution;
	int best;
	t_room *current;
	int tmp;
	int	diff;
	int previous;

	current = NULL;
	paths = 0;
	new_solution = -1;
	tmp = 0;
	best = -1;
	diff = 0;
	previous = -1;
	clean_previous_solution_marks(start_rooms);
	while ((current = get_next_path(start_rooms)))
	{
		if (paths > 0 && (ants - (diff + ((current->final_distance - previous) * paths))) / paths <= 0)
			break;
		if (paths > 0)
			diff += (current->final_distance - previous) * paths;
		paths += 1;
		current->solution_len = current->final_distance;
		tmp = ((ants - diff) / paths) + current->final_distance + ((ants - diff) % paths > 0 ? 1 : 0);
		if (new_solution < 0 || (tmp >= 0 && tmp < new_solution))
		{
			new_solution = tmp;
			if (new_solution < best || best < 0)
				best = new_solution;
			previous = current->final_distance;
		}
	}
	//ft_printf("best : %d\n", best);
	if (*solution < 0 || (best >= 0 && best <= *solution))
	{
		replace_previous_solution(start_rooms);
		t_node *ptr = start_rooms->head;
		t_room *lolptr;
		//ft_printf("Computed diff %d\n", diff);
		while (ptr)
		{
			lolptr = (*(t_room**)ptr->data);
			if (lolptr->solution_len >= 0)
			{
				//ft_printf("path %s of len %d\n", lolptr->name, lolptr->solution_len);
			}
			ptr = ptr->next;
		}
		//ft_putchar('\n');
		*solution = best;
	}
	t_node *node_ptr;
	node_ptr = start_rooms->head;
	while (node_ptr)
	{
		(*(t_room**)node_ptr->data)->recorded = 0;
		node_ptr = node_ptr->next;
	}
	return (0);
}
