/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_starting_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:11:23 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/20 18:46:19 by bopopovi         ###   ########.fr       */
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

static t_tmp	*create_new_path(t_room *head_room, int is_start)
{
	t_tmp	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	if (is_start)
		new->size = head_room->end_len;
	else
		new->size = head_room->start_len;
	new->path_id = 0;
	new->room = head_room;
	return (new);
}

static int		add_new_path(t_list *starting_paths, t_tmp **new_path, t_room *head, int is_start)
{
	if (!(*new_path = create_new_path(head, is_start)))
		return (-1);
	if (ft_lstadd_data(starting_paths, (void*)new_path, sizeof(void*)) < 0)
		return (-1);
	return (0);
}

static int		get_paths(t_list **starting_paths, t_room *source, int is_start)
{
	size_t	i;
	t_room	*head;
	t_tmp	*new_path;

	i = 0;
	head = NULL;
	if (!(*starting_paths = ft_lstnew()))
		return (-1);
	new_path = NULL;
	while (i < source->links->size)
	{
		head = ft_vector_get(source->links, i);
		if (add_new_path(*starting_paths, &new_path, head, is_start) < 0)
			return (-1);
		i++;
	}
	return (0);
}

t_list	 *get_initial_paths(t_room *source, int is_start)
{
	t_list *starting_paths;

	if (get_paths(&starting_paths, source, is_start) < 0)
		ft_lstdel(starting_paths, (void*)&del_tmp);
	return (starting_paths);
}
