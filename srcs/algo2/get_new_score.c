/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_score.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 21:23:42 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/13 16:40:40 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	add_path_to_score(t_score *score, t_path *path)
{
	score->nbr_of_paths += 1;
	score->output_size = ((score->total_ants - score->diff) / score->nbr_of_paths) + path->length + ((score->total_ants - score->diff) % score->nbr_of_paths > 0 ? 1 : 0);
	score->longest_path_size = path->length;
	path->final_length = path->length; //WILL BE USED TO RETRIEVE PATH IF SCORE IS BETTER
	path->length = -1;
}

int		update_score_if_improved_by_path(t_score *score, t_path *path)
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
		if (path_ptr->length >= 0 && path_ptr->head->recorded == 0)
		{
			if (!shortest || path_ptr->length < shortest->length)
			{
				if (!path_ptr->head->recorded) //recorded field to put into t_path
					shortest = path_ptr;
			}
		}
		node_ptr = node_ptr->next;
	}
	if (shortest)
		shortest->head->recorded = 1;
	return (shortest);
}

void	get_new_score(t_route *route, t_score **new_score)
{
	t_path *path;

	print_dbg(0, "Computing score for current route :\n", NULL);
	while ((path = get_next_shortest_path(route->paths)))
	{
		if (update_score_if_improved_by_path(*new_score, path))
		{
			print_dbg(0, "\tPath %s of length %d improves score, recording.\n", path->head->name, path->length);
			add_path_to_score(*new_score, path);
		}
		else
			path->length = -1;
	}
}
