/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/11/20 14:29:37 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_data(t_graph *graph, char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		ft_strdel(&input[i]);
		i++;
	}
	ft_strdel(&input[i]);
	free(input);
	input = NULL;
	graph->size = 0;
	graph->rooms = NULL;
}

int		main(void)
{
	/* Create needed structures */
	size_t		ants;
	t_graph		graph;
	char		**input;

	ants = 0;
	init_graph(&graph);
	/* Check and read input into previously created structures */
	input = get_input();
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	/* Clean allocated memory */
	/* Exit */
	free_data(&graph, input);
	return (0);
}
