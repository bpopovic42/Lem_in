/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 17:25:57 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/06 17:34:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bfs	*init_bfs_data(void)
{
	t_bfs *bfs_data;

	if (!(bfs_data = malloc(sizeof(*bfs_data))))
		return (NULL);
	bfs_data->all_paths = NULL;
	bfs_data->end_paths = NULL;
	bfs_data->end_sets = NULL;
	bfs_data->paths_nbr = 0;
	bfs_data->end_paths_nbr = 0;
	bfs_data->end_sets_nbr = 0;
	return (bfs_data);
}

int	bfs_add_path(t_bfs *bfs_data, t_path **path)
{
	if (ft_lstadd_data(&bfs_data->all_paths, path, sizeof(path)) < 0)
		return (-1);
	bfs_data->paths_nbr++;
	return (0);
}

int	bfs_add_end_path(t_bfs *bfs_data, t_path **path)
{
	if (ft_lstadd_data(&bfs_data->end_paths, path, sizeof(path)) < 0)
		return (-1);
	bfs_data->end_paths_nbr++;
	if (bfs_new_end_set(bfs_data, path) < 0)
		return (-1);
	return (0);
}

int	bfs_add_set(t_bfs *bfs_data, t_set **set)
{
	if (ft_lstadd_data(&bfs_data->end_sets, set, sizeof(set)) < 0)
		return (-1);
	bfs_data->end_sets_nbr++;
	return (0);
}

int	bfs_new_end_set(t_bfs *bfs_data, t_path **path)
{
	t_set *new_set;

	if (!(new_set = init_new_set(bfs_data->end_sets_nbr + 1)))
		return (-1);
	if (set_add_path(new_set, *path) < 0)
		return (-1);
	bfs_add_set(bfs_data, &new_set);
	// CONFLICT SORTING HERE
	return (0);
}

static void del_ptr(void ***ptr)
{
	void **to_free = *ptr;
	free(to_free);
	ft_bzero(&to_free, sizeof(to_free));
}

void	bfs_free(t_bfs *bfs_data)
{
	bfs_data->end_sets_nbr = 0;
	bfs_data->end_paths_nbr = 0;
	bfs_data->paths_nbr = 0;
	if (bfs_data->end_sets)
		ft_lstdel(&bfs_data->end_sets, (void*)&set_free); // Free set should call a del_ptr for its paths
	if (bfs_data->end_paths)
		ft_lstdel(&bfs_data->end_paths, (void*)&del_ptr); // Erase paths ptrs
	if (bfs_data->all_paths)
		ft_lstdel(&bfs_data->all_paths, (void*)&lst_free_path); // Finally free all the paths
	free(bfs_data);
}
