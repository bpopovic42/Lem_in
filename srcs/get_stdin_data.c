/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stdin_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:59:13 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/14 20:43:16 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_data(char **input)
{
	int i;

	i = -1;
	while (input[++i])
		ft_strdel(&input[i]);
	free(input);
	input = NULL;
}

static int		exit_error(const char *msg, char **input)
{
	free_data(input);
	ft_putendl_fd(msg, STDERR);
	return (-1);
}

int		get_stdin_data(unsigned int *ants_nbr, t_graph *graph)
{
	char			**input;

	init_graph(graph);
	input = input_to_array();
	if (get_ants_nbr(input, ants_nbr) < 0)
		return (-1);
	if (get_rooms(input, graph) < 0)
		return (-1);
	free_data(input);
	return (0);
}
