/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/26 19:15:43 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

static void		free_data(t_graph *graph, char **file)
{
	graph->size = 0;
	if (*file)
		ft_strdel(file);
	if (graph->room_list)
	{
		ft_vector_free(graph->room_list, (void(*)(void**))&ft_strdel);
		graph->room_list = NULL;
	}
	if (graph->rooms)
	{
		ft_hash_freetable(graph->rooms->table, graph->rooms->size, &free_room);
		free(graph->rooms);
		graph->rooms = NULL;
	}
}

static int		exit_error(t_graph *graph, char **file)
{
	free_data(graph, file);
	return (-1);
}

void			lemin_perror(const char *msg)
{
	if (ERR_DBG)
		ft_printf("{red}");
	ft_putstr("ERROR");
	if (ERR_DBG)
		ft_printf(": %s{eoc}\n", msg);
}

int		main(void)
{
	int		ants;
	char	*file;
	t_graph	graph;

	ants = 0;
	file = NULL;
	init_graph(&graph);
	if (parse_input(&ants, &graph, &file) < 0)
		return (exit_error(&graph, &file));
	if (!graph.start || !graph.end)
	{
		lemin_perror("No start and/or end room.");
		return (exit_error(&graph, &file));
	}
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	ft_printf("%s\n", file);
	ft_printf("Nbr of rooms = [%d]\n", graph.size);
	ft_printf("Start = [%s]\n", graph.start->name);
	ft_printf("Pos = [%d,%d]\n\n", graph.start->pos.x, graph.start->pos.y);
	free_data(&graph, &file);
	return (0);
}
