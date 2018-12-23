/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/23 01:36:23 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

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
	if (graph->room_list)
	{
		ft_vector_free(graph->room_list, (void(*)(void*))&ft_strdel);
		graph->room_list = NULL;
	}
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
	lemin_perror(msg, 1);
	return (-1);
}

void			lemin_perror(const char *msg, int critical)
{
	if (ERR_DBG)
		ft_printf(critical ? "{red}" : "{yellow}");
	if (critical || ERR_DBG)
		ft_putstr("ERROR");
	if (ERR_DBG)
	{
		ft_printf(": %s{eoc}\n", msg);
	}
}

int		main(void)
{
	unsigned int	ants_nbr;
	t_graph			graph;

	ants_nbr = 0;
	init_graph(&graph);
	if (parse_input(&ants_nbr, &graph) < 0)
		return (exit_error("main: input error", &graph));
	if (!graph.start || !graph.end)
		return (exit_error("main: missing start or end room", &graph));

	ft_printf("\nStart = [%s]\n", graph.start->name);
	ft_printf("Pos = [%d,%d]\n\n", graph.start->pos.x, graph.start->pos.y);
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	/* Clean allocated memory */
	/* Exit */
	free_data(&graph);
	return (0);
}
