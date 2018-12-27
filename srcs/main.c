/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 22:56:40 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/27 13:51:53 by bopopovi         ###   ########.fr       */
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

static void		display_links_for_room(t_room *room)
{
	size_t	i;

	i = 0;
	if (room->links)
	{
		while (i < room->links->size)
		{
			ft_printf("%s\t\t->\t%s\n", room->name, room->links->data[i]);
			i++;
		}
	}
}

static void		display_links_for_all_rooms(t_graph *graph)
{
	size_t	i;
	t_room	*ptr;

	i = 0;
	ptr = NULL;
	ft_printf("LINKS:\n");
	if (graph->room_list && graph->size)
	{
		while (i < graph->size)
		{
			ptr = ft_hashget_data(graph->rooms, graph->room_list->data[i]);
			display_links_for_room(ptr);
			i++;
		}
	}
}

static void		print_room(t_room *room)
{
	size_t	i;

	i = 0;
	ft_printf("%s\t\t:\t", room->name);
	ft_printf("[ %d , %d ]", room->pos.x, room->pos.y);
	if (room->command)
		ft_printf("\t<- %s\n", room->command);
	else
		ft_putchar('\n');
}

static void		print_all_rooms(t_graph *graph)
{
	size_t	i;
	t_room	*ptr;

	i = 0;
	ptr = NULL;
	ft_printf("ROOMS: ( %d )\n", graph->size);
	if (graph->room_list && graph->size)
	{
		while (i < graph->size)
		{
			ptr = ft_hashget_data(graph->rooms, graph->room_list->data[i]);
			print_room(ptr);
			i++;
		}
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
	if (parse_input(&ants, &graph, &file) < 0)
		return (exit_error(&graph, &file));
	if (!graph.start || !graph.end)
	{
		lemin_perror("No start and/or end room.");
		return (exit_error(&graph, &file));
	}
	//else if (!graph.links->size)
	//{
	//	lemin_perror("No links provided.");
	//	return (exit_error(&graph, &file));
	//}
	/* Apply path-finding algorithm to find shortest paths */
	/* Apply algorithm to find most efficient paths depending on ants quantity */
	/* Output solution */
	ft_printf("%s\n", file);
	print_all_rooms(&graph);
	ft_putchar('\n');
	display_links_for_all_rooms(&graph);
	free_data(&graph, &file);
	return (0);
}
