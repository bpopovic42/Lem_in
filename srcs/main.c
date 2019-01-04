/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/01/04 18:30:10 by bopopovi         ###   ########.fr       */
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

static int	input_is_valid(int ants, t_graph *graph, char *last_line)
{
	if (ants <= 0)
	{
		lemin_perror(EINVANT, last_line);
		return (0);
	}
	else if (graph->nbr_of_rooms < 2)
	{
		lemin_perror(ENEROOM, last_line);
		return (0);
	}
	else if (graph->nbr_of_links < 1)
	{
		lemin_perror(ENELINK, last_line);
		return (0);
	}
	else if (!graph->start || !graph->end)
	{
		lemin_perror(EINVMAP, last_line);
		return (0);
	}
	return (1);
}

int		main(void)
{
	int		ants;
	char	*file;
	t_graph	graph;
	char	*last_line_read;

	ants = 0;
	file = NULL;
	init_graph(&graph);
	last_line_read = parse_input(&ants, &graph, &file);
	if (!input_is_valid(ants, &graph, last_line_read))
		return (local_exit(&graph, &file, 1));
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	print_result(&graph, file);
	return (local_exit(&graph, &file, 0));
}
