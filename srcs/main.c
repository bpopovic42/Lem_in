/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2019/04/03 02:22:40 by bopopovi         ###   ########.fr       */
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

int		main(void)
{
	int		ants;
	char	*file;
	t_graph	graph;

	ants = 0;
	file = NULL;
	if (init_graph(&graph) < 0)
		return (1);
	if (parse_input(&ants, &graph, &file) != 0)
		return (local_exit(&graph, &file, 1));
	if (find_best_path_combination(ants, &graph) < 0)
		return (local_exit(&graph, &file, 1));
	return (local_exit(&graph, &file, 0));
}
