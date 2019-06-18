/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_score.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:23:42 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 19:26:20 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		add_path_to_score(t_score *s, t_path *path)
{
	s->nbr_of_paths += 1;
	s->output_size = ((s->total_ants - s->diff) / s->nbr_of_paths)
		+ path->length + ((s->total_ants - s->diff)
			% s->nbr_of_paths > 0 ? 1 : 0);
	s->longest_path_size = path->length;
	path->final_length = path->length;
	path->length = -1;
}

static int		update_score_if_improved_by_path(t_score *score, t_path *path)
{
	int new_diff;
	int new_score;
	int ants_left;

	if (score->nbr_of_paths == 0)
		return (1);
	new_diff = path->length - score->longest_path_size;
	new_diff *= score->nbr_of_paths;
	new_diff += score->diff;
	ants_left = score->total_ants - new_diff;
	if (ants_left > 0 && ants_left / (score->nbr_of_paths + 1) > 0)
	{
		new_score = ants_left / (score->nbr_of_paths + 1);
		new_score += path->length;
		new_score += (ants_left % (score->nbr_of_paths + 1) > 0);
		if (score->output_size < 0 || new_score < score->output_size)
		{
			score->diff = new_diff;
			return (1);
		}
	}
	return (0);
}

static t_path	*get_next_shortest_path(t_list *paths)
{
	t_node *node_ptr;
	t_path *path_ptr;
	t_path *shortest;

	node_ptr = paths->head;
	path_ptr = NULL;
	shortest = NULL;
	while ((path_ptr = get_path_from_node(node_ptr)))
	{
		if (path_ptr->length >= 0 && path_ptr->recorded == 0)
		{
			if (!shortest || path_ptr->length < shortest->length)
			{
				if (!path_ptr->recorded)
					shortest = path_ptr;
			}
		}
		node_ptr = node_ptr->next;
	}
	if (shortest)
		shortest->recorded = 1;
	return (shortest);
}

void			get_new_score(t_route *route, t_score *new_score)
{
	t_path *path;

	print_dbg(0, "Computing score for current route :\n", NULL);
	while ((path = get_next_shortest_path(route->paths)))
	{
		if (update_score_if_improved_by_path(new_score, path))
		{
			print_dbg(0, "\tPath %s of length %d improves score, recording.\n",
				path->head->name, path->length);
			add_path_to_score(new_score, path);
		}
		else
			path->length = -1;
	}
}
