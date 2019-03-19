/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_starting_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:11:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/19 14:07:02 by bopopovi         ###   ########.fr       */
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

static t_tmp	*new_initial_room(size_t size, t_room *room_ptr)
{
	t_tmp	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->size = size;
	new->path_id = 0;
	new->room = room_ptr;
	return (new);
}

static t_list	*get_initial_rooms(t_room *source, int is_start)
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
	while (i < source->links->size)
	{
		ptr = ft_vector_get(source->links, i);
		if (is_start)
			initial_room = new_initial_room(ptr->end_len, ptr);
		else
			initial_room = new_initial_room(ptr->start_len, ptr);
		if (!initial_room)
			return (NULL);//
		if (ft_lstadd_data(path_list, (void*)&initial_room, sizeof(void*)) < 0)
			return (NULL);//
		i++;
	}
	return (path_list);
}

t_list	 *get_starting_paths(t_room *source, int is_start)
{
	t_list *path_list;

	if (!(path_list = get_initial_rooms(source, is_start)))
		ft_lstdel(path_list, (void*)&del_tmp);
	return (path_list);
}
