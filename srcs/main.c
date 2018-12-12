/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/12 19:44:25 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void		free_room(void *room)
{
	ft_strdel((char**)&room);
	free(room);
}

static void		free_hashtable(t_htable *hash_table)
{
	size_t	i;
	t_hash	*ptr;

	i = 0;
	while (i < hash_table->size)
	{
		if (hash_table->table[i])
		{
			if (hash_table->table[i]->next)
			{
				ptr = hash_table->table[i]->next;
				while (ptr)
				{
					free(ptr->data);
					ptr->data = NULL;
					ptr = ptr->next;
				}
			}
		}
		free(hash_table->table[i]);
		i++;
	}
	free(hash_table->table);
	free(hash_table);
}

static void		free_data(t_graph *graph, char **input)
{
	int i;

	i = 0;
	while (input[i])
	{
		ft_strdel(&input[i]);
		i++;
	}
	ft_strdel(&input[i]);
	free(input);
	input = NULL;
	graph->size = 0;
	ft_vector_free(graph->rooms_list, &free_room);
	free_hashtable(graph->rooms);
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
	ft_printf("Ants nbr = %d\n", ants);
	size_t i = 0;
	t_room *ptr;
	t_hash *hash;
	while (i < graph.rooms_list->size)
	{
		hash = ft_hashget(graph.rooms, graph.rooms_list->data[i]);
		ptr = hash->data;
		ft_printf("Room [%s] :\n", ptr->name);
		ft_printf("Comment = %s\n", ptr->comment);
		ft_printf("Position = %d, %d\n\n", ptr->position->x, ptr->position->y);
		i++;
	}

	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	/* Clean allocated memory */
	/* Exit */
	free_data(&graph, input);
	return (0);
}
