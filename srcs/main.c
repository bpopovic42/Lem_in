/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/27 17:20:41 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

static void		local_free(t_graph *graph, char **file)
{
	graph->nbr_of_rooms = 0;
	graph->nbr_of_links = 0;
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

static int		local_exit(char *msg, t_graph *graph, char **file, int retval)
{
	if (msg && retval < 0)
		lemin_perror((const char*)msg);
	local_free(graph, file);
	return (retval);
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
		return (local_exit(NULL, &graph, &file, -1));
	else if (!graph.nbr_of_rooms)
		return (local_exit("No rooms provided.", &graph, &file, -1));
	else if (!graph.nbr_of_links)
		return (local_exit("No links provided.", &graph, &file, -1));
	else if (!graph.start || !graph.end)
		return (local_exit("No start and/or end room.", &graph, &file, -1));
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	print_result(&graph, file);
	return (local_exit(NULL, &graph, &file, 0));
}
