/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/11/27 19:55:28 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_room(void *room)
{
	t_room *data;

	data = (t_room*)room;
	if (data->comment)
		free(data->comment);
	if (data->name)
		free(data->name);
	if (data->links)
		free(data->links);
	if (data->position)
		free(data->position);

}

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
	ft_vector_free(graph->rooms, &free_room);
	graph->rooms = NULL;
}

static int		exit_error(const char *msg, t_graph *graph, char **input)
{
	free_data(graph, input);
	ft_putendl(msg);
	return (-1);
}

int		main(void)
{
	/* Create needed structures */
	unsigned int	ants;
	t_graph			graph;
	char			**input;

	ants = 0;
	init_graph(&graph);
	/* Check and read input into previously created structures */
	input = get_input();
	if (get_ants_nbr(input, &ants) < 0)
		exit_error("main: invalid ants input", &graph, input);
	if (get_rooms(input, &graph) < 0)
		exit_error("main: bad formatted rooms input", &graph, input);
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	/* Clean allocated memory */
	/* Exit */
	free_data(&graph, input);
	return (0);
}
