/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/15 21:03:05 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

static int		local_exit(t_graph *graph, char **file, int retval)
{
	if (*file)
		ft_strdel(file);
	free_graph(graph);
	return (retval);
}

static void	print_next_rooms(t_room *target, int from_start)
{
	size_t	i;
	int		*target_depth;
	t_room *ptr;

	i = 0;
	while (i < target->links->size)
	{
		ptr = ft_vector_get(target->links, i);
		target_depth = from_start ? &ptr->end_len : &ptr->start_len;
		ft_printf("Room '%s' depth = %d\n", ptr->name, *target_depth);
		i++;
	}
}

int		main(void)
{
	int		ants;
	char	*file;
	t_graph	graph;

	ants = 0;
	file = NULL;
	init_graph(&graph);
	if (parse_input(&ants, &graph, &file) != 0)
		return (local_exit(&graph, &file, 1));
	if (weight_graph(graph.end, 0) < 0)
		return (local_exit(&graph, &file, 1));
	print_next_rooms(graph.start, 1);
	if (weight_graph(graph.start, 1) < 0)
		return (local_exit(&graph, &file, 1));
	print_next_rooms(graph.end, 0);
	if (get_best_route(&graph) < 0)
		return (local_exit(&graph, &file, 1));
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	//print_result(&graph, file);
	return (local_exit(&graph, &file, 0));
}
