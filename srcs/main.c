/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/13 20:05:29 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void		free_room(void *room)
{
	if (((t_room*)room)->comment != NULL)
		ft_strdel(&(((t_room*)room)->comment));
	ft_strdel(&(((t_room*)room)->name));
	//free(((t_room*)room)->links);
	((t_room*)room)->pos.x = 0;
	((t_room*)room)->pos.y = 0;
	free(room);
}

static void		free_data(t_graph *graph, char **input)
{
	int i;

	i = -1;
	while (input[++i])
		ft_strdel(&input[i]);
	free(input);
	input = NULL;
	graph->size = 0;
	ft_hash_freetable(graph->rooms->table, graph->rooms->size, &free_room);
	free(graph->rooms);
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
	ft_printf("Ants nbr = %d\n\n", ants);

	ft_printf("Start = [%s]\n", graph.start->name);
	ft_printf("Pos = [%d,%d]\n\n", graph.start->pos.x, graph.start->pos.y);
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	/* Clean allocated memory */
	/* Exit */
	free_data(&graph, input);
	return (0);
}
