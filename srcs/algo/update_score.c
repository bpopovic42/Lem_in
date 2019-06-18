/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_score.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:05:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 19:34:47 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	remove_previous_route_marks(t_graph *graph)
{
	t_room *next_ptr;
	size_t i;

	i = 0;
	while (i < graph->room_list->size)
	{
		next_ptr = ft_vector_get(graph->room_list, i);
		if (!room_is_start(next_ptr))
		{
			next_ptr->solution_len = -1;
			next_ptr->solution_from = NULL;
			next_ptr->solution_to = NULL;
		}
		i++;
	}
}

static int	new_score_is_better(t_score *previous, t_score *new)
{
	if (!previous || previous->output_size < 0)
		return (1);
	if ((new->output_size >= 0 && new->output_size < previous->output_size))
		return (1);
	return (0);
}

static void	replace_score(t_score *old_score, t_score *new_score)
{
	old_score->total_ants = new_score->total_ants;
	old_score->diff = new_score->diff;
	old_score->output_size = new_score->output_size;
	old_score->nbr_of_paths = new_score->nbr_of_paths;
	old_score->longest_path_size = new_score->longest_path_size;
}

int			update_score(t_graph *graph, t_route *route)
{
	t_score new_score;

	init_score(&new_score);
	new_score.total_ants = graph->ants;
	get_new_score(route, &new_score);
	if (new_score_is_better(route->score, &new_score))
	{
		print_dbg(1, "ROUTE IS BETTER", NULL);
		replace_score(route->score, &new_score);
		ft_lstiter(route->paths, (void*)&path_remove_solution_mark);
		remove_previous_route_marks(graph);
		mark_new_route(route);
	}
	ft_lstiter(route->paths, (void*)&path_remove_recorded_mark);
	return (0);
}
