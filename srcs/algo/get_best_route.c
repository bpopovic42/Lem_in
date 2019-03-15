/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_best_route.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:11:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/15 20:28:18 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		del_tmp(void *data, size_t data_size)
{
	t_tmp **tmp;

	tmp = *(t_tmp***)data;
	ft_bzero(tmp, data_size);
	free(*tmp);
	ft_bzero(&tmp, sizeof(tmp));
	free(tmp);

}

static int		local_exit(t_list *path_list, int status)
{
	ft_lstdel(path_list, (void*)&del_tmp);
	return (status);
}

static t_tmp	*new_initial_room(size_t size, t_room *room_ptr)
{
	t_tmp	*new;

	if (!(new = malloc(sizeof(new))))
		return (NULL);
	new->size = size;
	new->room = room_ptr;
	return (new);
}

static t_list	*get_initial_rooms(t_room *start)
{
	size_t	i;
	t_room	*ptr;
	t_list	*path_list;
	t_tmp	*initial_room;

	i = 0;
	ptr = NULL;
	if (!(path_list = ft_lstnew()))
		return (NULL);
	initial_room = NULL;
	while (i < start->links->size)
	{
		ptr = ft_vector_get(start->links, i);
		if (!(initial_room = new_initial_room(ptr->depth, ptr)))
			return (NULL);//
		if (ft_lstadd_data(path_list, (void*)&initial_room, sizeof(void*)) < 0)
			return (NULL);//
		i++;
	}
	return (path_list);
}

#include "ft_printf.h"

static void tmp_print(t_list *path_list)
{
	t_tmp *tmp;
	t_node *ptr;

	ptr = path_list->head;
	while (ptr)
	{
		tmp = *(t_tmp**)ptr->data;
		ft_printf("Path %s of size %d\n", tmp->room->name, tmp->size);
		ptr = ptr->next;
	}
}

int				get_best_route(t_graph *graph)
{
	t_list *path_list;

	if (!(path_list = get_initial_rooms(graph->start)))
		return (local_exit(path_list, -1));
	tmp_print(path_list);
	return (local_exit(path_list, 0));
}
