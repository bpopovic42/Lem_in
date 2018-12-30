/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:40:03 by bopopovi          #+#    #+#             */
/*   Updated: 2018/12/30 19:56:03 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void		free_room(void *room)
{
	if (((t_room*)room)->command != NULL)
		ft_strdel(&(((t_room*)room)->command));
	ft_strdel(&(((t_room*)room)->name));
	if (((t_room*)room)->links)
		ft_vector_free(((t_room*)room)->links, (void*)(void**)&ft_strdel);
	((t_room*)room)->pos.x = 0;
	((t_room*)room)->pos.y = 0;
	free(room);
}

void	init_graph(t_graph *graph)
{
	graph->nbr_of_rooms = 0;
	graph->nbr_of_links = 0;
	graph->start = NULL;
	graph->end = NULL;
	graph->room_list = ft_vector_init(sizeof(char*), 0);
	graph->command_list = ft_vector_init(sizeof(t_cmd*), 0);
	graph->rooms = ft_hash_newtable(100);
}

static void	free_command(t_cmd **command)
{
	if (command)
	{
		if ((*command)->command)
			ft_strdel(&((*command)->command));
		if ((*command)->room_name)
			ft_strdel(&((*command)->room_name));
	}
}

void		free_graph(t_graph *graph)
{
	if (graph->room_list)
		ft_vector_free(graph->room_list, (void(*)(void**))&ft_strdel);
	if (graph->command_list)
		ft_vector_free(graph->command_list, (void(*)(void**))&free_command);
	if (graph->rooms)
		ft_hash_freetable(&graph->rooms, &free_room);
	graph->nbr_of_rooms = 0;
	graph->nbr_of_links = 0;
	graph->room_list = NULL;
	graph->command_list = NULL;
	graph->rooms = NULL;
}

void			lemin_perror(const char *msg)
{
	if (ERR_DBG)
		ft_printf("{red}");
	ft_putstr("ERROR");
	if (ERR_DBG)
		ft_printf(": %s{eoc}\n", msg);
}

char	*get_last_command(t_graph *graph)
{
	t_cmd *ptr;

	ptr = ft_vector_get(graph->command_list, graph->command_list->size);
	if (ptr && ptr->command)
		return (ptr->command);
	else
		return (NULL);
}
