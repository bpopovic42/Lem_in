/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_debug_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 17:01:50 by bopopovi          #+#    #+#             */
/*   Updated: 2019/03/05 16:50:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	print_set(t_set *set)
{
	t_list *ptr;
	int i;

	ptr = set->paths;
	i = 0;
	while (ptr)
	{
		ft_printf("Path %d :\n", i);
		print_path(*((t_path**)ptr->content));
		ft_putchar('\n');
		ptr = ptr->next;
		i++;
	}
}

void	print_path(t_path *path)
{
	t_dlist *ptr;

	if (path)
	{
		ft_printf("ID : %d\n", path->id);
		ptr = path->head;
		while (ptr)
		{
			ft_putendl((*((t_room**)ptr->content))->name);
			ptr = ptr->next;
		}
	}
}

void print_end_sets(t_bfs *bfs_data)
{
	t_list *ptr;
	int		i;

	ptr = bfs_data->end_sets;
	i = 0;
	ft_putendl("lol");
	while (ptr)
	{
		ft_printf("\n###### SET %d #####\n\n", i);
		print_set(*(t_set**)ptr->content);
		ft_printf("###### SET END ######\n");
		ptr = ptr->next;
		i++;
	}
}
