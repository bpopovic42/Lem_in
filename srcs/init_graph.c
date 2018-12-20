/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 23:17:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/20 15:53:39 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_graph(t_graph *graph)
{
	graph->size = 0;
	graph->start = NULL;
	graph->end = NULL;
	graph->room_list = ft_vector_init(sizeof(char*), 0);
	graph->rooms = ft_hash_newtable(100);
}
