/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 23:17:42 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/13 18:15:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_graph(t_graph *graph)
{
	graph->size = 0;
	graph->start = NULL;
	graph->end = NULL;
	graph->rooms = NULL;
}
