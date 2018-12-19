/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/19 17:53:24 by bopopovi         ###   ########.fr       */
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

static void		free_data(t_graph *graph)
{
	graph->size = 0;
	if (graph->rooms)
	{
		ft_hash_freetable(graph->rooms->table, graph->rooms->size, &free_room);
		free(graph->rooms);
		graph->rooms = NULL;
	}
}

static int		exit_error(const char *msg, t_graph *graph)
{
	free_data(graph);
	ft_putendl_fd(msg, STDERR);
	return (-1);
}

int		main(void)
{
	unsigned int	ants_nbr;
	t_graph			graph;


	if (parse_input(&ants_nbr, &graph) < 0)
		return (exit_error("main: input error", &graph));
	if (!graph.start || !graph.end)
		return (exit_error("main: missing start or end room", &graph));

	ft_printf("Ants nbr = %d\n\n", ants_nbr);
	ft_printf("Start = [%s]\n", graph.start->name);
	ft_printf("Pos = [%d,%d]\n\n", graph.start->pos.x, graph.start->pos.y);
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	/* Clean allocated memory */
	/* Exit */
	free_data(&graph);
	return (0);
}
