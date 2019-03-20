/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:11:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/20 19:23:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		del_tmp(void *data, size_t data_size)
{
	t_path **tmp;

	tmp = *(t_path***)data;
	ft_bzero(tmp, data_size);
	free(*tmp);
	ft_bzero(&tmp, sizeof(tmp));
	free(tmp);
}

static t_path	*create_new_path(t_room *head_room, int is_start)
{
	t_path	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	if (is_start)
		new->size = head_room->end_len;
	else
		new->size = head_room->start_len;
	new->path_id = 0;
	new->head = head_room;
	return (new);
}

static int		add_new_path(t_list *paths_list, t_path **new_path, t_room *head, int is_start)
{
	if (!(*new_path = create_new_path(head, is_start)))
		return (-1);
	if (ft_lstadd_data(paths_list, (void*)new_path, sizeof(void*)) < 0)
		return (-1);
	return (0);
}

t_list			*get_paths(t_room *source, int is_start)
{
	size_t	i;
	t_room	*head;
	t_path	*new_path;
	t_list	*paths_list;

	i = 0;
	head = NULL;
	new_path = NULL;
	if (!(paths_list = ft_lstnew()))
		return (NULL);
	while (i < source->links->size)
	{
		head = ft_vector_get(source->links, i);
		if (add_new_path(paths_list, &new_path, head, is_start) < 0)
		{
			ft_lstdel(paths_list, (void*)&del_tmp);
			return (NULL);
		}
		i++;
	}
	return (paths_list);
}
