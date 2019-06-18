/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_remove_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:33:33 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 19:34:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	path_remove_recorded_mark(t_path ***path_container)
{
	t_path *path;

	path = **path_container;
	path->recorded = 0;
}

void	path_remove_solution_mark(t_path ***path_container)
{
	t_path *path;

	path = **path_container;
	path->is_solution = 0;
}
