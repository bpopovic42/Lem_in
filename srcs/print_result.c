/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:18:05 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/27 15:22:32 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void		print_links_for_room(t_room *room)
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

void		print_links_for_all_rooms(t_graph *graph)
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
			print_links_for_room(ptr);
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

void		print_all_rooms(t_graph *graph)
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

void		print_result(t_graph *graph, char *file)
{
	ft_printf("%s\n", file);
	print_all_rooms(graph);
	ft_putchar('\n');
	print_links_for_all_rooms(graph);
}
