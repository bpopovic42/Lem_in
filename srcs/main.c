/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/30 18:46:32 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

__attribute__((unused)) static int fun_abs(int a)
{
	return (a * (1 - 2 * (a < 0)));
}

static int		local_exit(char *msg, t_graph *graph, char **file, int retval)
{
	if (msg && retval < 0)
		lemin_perror((const char*)msg);
	if (*file)
		ft_strdel(file);
	free_graph(graph);
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
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	print_result(&graph, file);
	return (local_exit(NULL, &graph, &file, 0));
}
