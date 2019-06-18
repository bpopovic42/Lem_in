/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_set_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:13:37 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 19:14:00 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	path_set_head(t_path *path, t_room *head)
{
	path->head = head;
}

void	path_set_final_length(t_path *path, int final_length)
{
	path->final_length = final_length;
}

void	path_set_length(t_path *path, int length)
{
	path->length = length;
}
